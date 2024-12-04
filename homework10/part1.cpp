#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <cmath>
#include <chrono>
#include <future>
#include <atomic>
#include <mutex>

// Function to be integrated
auto f = [](double x) { return x * x * x - 3 * x * x + 2; };

// Non-adaptive Trapezoidal Integration
void parallel_non_adaptive_trapezoidal(double a, double b, int n, int num_threads, std::function<double(double)> func, double &result) {
    double h = (b - a) / n;
    std::vector<std::future<double>> futures;
    std::atomic<int> function_evals(0);
    std::mutex result_mutex;

    auto worker = [&](int start, int end) -> double {
        double local_result = 0.0;
        for (int i = start; i < end; ++i) {
            double x1 = a + i * h;
            double x2 = a + (i + 1) * h;
            local_result += 0.5 * h * (func(x1) + func(x2));
            function_evals += 2;
        }
        return local_result;
    };

    int chunk_size = n / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? n : start + chunk_size;
        futures.push_back(std::async(std::launch::async, worker, start, end));
    }

    for (auto &fut : futures) {
        double local_result = fut.get();
        std::lock_guard<std::mutex> lock(result_mutex);
        result += local_result;
    }

    std::cout << "Total Function Evaluations: " << function_evals.load() << std::endl;
}

int main() {
    double a = 0.0, b = 2.0;
    std::vector<int> ns = {1000, 10000, 100000};
    std::vector<int> thread_counts = {1, 2, 4, 8, 16};

    for (int n : ns) {
        for (int t : thread_counts) {
            double result = 0.0;
            auto start_time = std::chrono::high_resolution_clock::now();

            parallel_non_adaptive_trapezoidal(a, b, n, t, f, result);

            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end_time - start_time;

            // Output results
            std::cout << "n: " << n << ", threads: " << t << ", integral: " << result
                      << ", time: " << elapsed.count() << "s" << std::endl;
        }
    }

    return 0;
}
