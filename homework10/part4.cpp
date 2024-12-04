#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <chrono>
#include <cmath>
#include <numeric>
#include <mutex>

// Function to be integrated
auto f = [](double x) { return x * x * x - 3 * x * x + 2; };

// Trapezoidal Integration over a range [a, b] with n intervals
double trapezoidal(double a, double b, int n, std::function<double(double)> func) {
    double h = (b - a) / n;
    double result = 0.5 * (func(a) + func(b));
    for (int i = 1; i < n; ++i) {
        result += func(a + i * h);
    }
    return result * h;
}

// Threaded function to calculate the integral over a subinterval
double thread_trapezoidal(double a, double b, int n, std::function<double(double)> func) {
    double h = (b - a) / n;
    double result = 0.5 * (func(a) + func(b));
    for (int i = 1; i < n; ++i) {
        result += func(a + i * h);
    }
    return result * h;
}

int main() {
    double a = 0.0, b = 2.0;
    std::vector<int> n_values = {1000, 10000, 100000};
    std::vector<int> thread_counts = {1, 2, 4, 8, 16};

    // High-precision sequential integration as reference
    int high_precision_n = 1000000; // Using a large value for n to increase precision
    double high_precision_result = trapezoidal(a, b, high_precision_n, f);
    std::cout << "High-Precision Sequential Result: " << high_precision_result << "\n\n";

    for (int n : n_values) {
        for (int t : thread_counts) {
            double h = (b - a) / t;
            std::vector<std::thread> threads;
            double total_result = 0.0;
            std::mutex result_mutex;

            auto start_time = std::chrono::high_resolution_clock::now();

            // Launch threads
            for (int i = 0; i < t; ++i) {
                double local_a = a + i * h;
                double local_b = local_a + h;
                threads.emplace_back([&, local_a, local_b]() {
                    double local_result = thread_trapezoidal(local_a, local_b, n / t, f);
                    std::lock_guard<std::mutex> lock(result_mutex);
                    total_result += local_result;
                });
            }

            // Join threads
            for (auto &th : threads) {
                th.join();
            }

            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end_time - start_time;

            // Calculate numerical error
            double error = fabs(total_result - high_precision_result);

            // Output results
            std::cout << "n: " << n << ", threads: " << t 
                      << ", integral: " << total_result
                      << ", time: " << elapsed.count() << "s"
                      << ", error: " << error << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
