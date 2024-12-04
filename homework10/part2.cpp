#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <chrono>
#include <cmath>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <memory>

// Function to be integrated
auto f = [](double x) { return std::sqrt(x) * (1 - x) * (1 - x); };

struct ThreadPool {
    explicit ThreadPool(size_t num_threads);
    ~ThreadPool();
    template<class F>
    auto enqueue(F&& f) -> std::future<typename std::result_of<F()>::type>;
    size_t get_num_workers() const;

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

ThreadPool::ThreadPool(size_t num_threads) : stop(false) {
    for (size_t i = 0; i < num_threads; ++i) {
        workers.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queue_mutex);
                    this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                    if (this->stop && this->tasks.empty())
                        return;
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers)
        worker.join();
}

template<class F>
auto ThreadPool::enqueue(F&& f) -> std::future<typename std::result_of<F()>::type> {
    using return_type = typename std::result_of<F()>::type;
    auto task = std::make_shared<std::packaged_task<return_type()>>(std::forward<F>(f));
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");
        tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
}

size_t ThreadPool::get_num_workers() const {
    return workers.size();
}

// Adaptive Trapezoidal Integration
void adaptive_trapezoidal(double a, double b, double tol, std::function<double(double)> func, ThreadPool &pool, double &result, std::atomic<int> &function_evals, std::mutex &result_mutex) {
    struct Task {
        double a, b, tol, fa, fb, fc, S;
    };

    std::queue<Task> task_queue;
    std::mutex task_mutex;

    auto initial_h = (b - a) / 2.0;
    double fa = func(a);
    double fb = func(b);
    double fc = func(a + initial_h);
    function_evals += 3;
    double S = (initial_h / 2.0) * (fa + 2 * fc + fb);

    task_queue.push(Task{a, b, tol, fa, fb, fc, S});

    auto worker = [&]() {
        while (true) {
            Task task;
            {
                std::lock_guard<std::mutex> lock(task_mutex);
                if (task_queue.empty()) {
                    return;
                }
                task = task_queue.front();
                task_queue.pop();
            }

            double h = (task.b - task.a) / 2.0;
            double fd = func(task.a + h / 2.0);
            double fe = func(task.a + 3 * h / 2.0);
            function_evals += 2;
            double S_left = (h / 2.0) * (task.fa + 2 * fd + task.fc);
            double S_right = (h / 2.0) * (task.fc + 2 * fe + task.fb);
            double S2 = S_left + S_right;

            if (std::abs(S2 - task.S) < 15 * task.tol) {
                std::lock_guard<std::mutex> lock(result_mutex);
                result += S2 + (S2 - task.S) / 15;
            } else {
                std::lock_guard<std::mutex> lock(task_mutex);
                task_queue.push(Task{task.a, task.a + h, task.tol / 2.0, task.fa, task.fc, fd, S_left});
                task_queue.push(Task{task.a + h, task.b, task.tol / 2.0, task.fc, task.fb, fe, S_right});
            }
        }
    };

    std::vector<std::future<void>> futures;
    for (size_t i = 0; i < pool.get_num_workers(); ++i) {
        futures.push_back(pool.enqueue(worker));
    }

    for (auto &future : futures) {
        future.get();
    }
}

int main() {
    double a = 0.0, b = 1.0;
    std::vector<double> tolerances = {1e-3, 1e-6};
    std::vector<int> thread_counts = {1, 2, 4, 8, 16};

    for (double tol : tolerances) {
        for (int t : thread_counts) {
            ThreadPool pool(t);
            double result = 0.0;
            std::atomic<int> function_evals(0);
            std::mutex result_mutex;

            auto start_time = std::chrono::high_resolution_clock::now();

            adaptive_trapezoidal(a, b, tol, f, pool, result, function_evals, result_mutex);

            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end_time - start_time;

            // Output results
            std::cout << "tol: " << tol << ", threads: " << t << ", integral: " << result
                      << ", time: " << elapsed.count() << "s"
                      << ", function evaluations: " << function_evals.load() << std::endl;
        }
    }

    return 0;
}
