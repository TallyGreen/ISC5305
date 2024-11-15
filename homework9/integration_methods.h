#ifndef INTEGRATION_METHODS_H
#define INTEGRATION_METHODS_H

#include <functional>
#include <vector>
#include <cmath>
#include <string>

// Alias for mathematical function type
using MathFunction = std::function<double(double)>;

struct Interval {
    double a, b;    // Interval boundaries
    double fa, fb;  // Function values at boundaries
    double area;    // Area of the interval
    int depth;      // Depth of recursion
};

struct IntegrationResults {
    std::string method_name;            // Name of the integration method
    std::string function_name;          // Name of the function being integrated
    std::string cache_type;             // Type of caching used (if any)
    int nb_intervals_or_max_depth;      // Number of intervals or maximum depth
    bool recursive;                     // Whether the method is recursive
    double numerical_result;            // Numerical result of the integration
    double analytical_result;           // Analytical result (if available, otherwise -1)
    double absolute_error;              // Absolute error (if available, otherwise -1)
    double execution_time;              // Time taken to perform the integration

    // Constructor with all fields
    IntegrationResults(const std::string& method, const std::string& func,
                       const std::string& cache, int intervals_or_depth,
                       bool is_recursive, double num_result, 
                       double anal_result, double abs_error)
        : method_name(method), function_name(func), cache_type(cache),
          nb_intervals_or_max_depth(intervals_or_depth),
          recursive(is_recursive), numerical_result(num_result),
          analytical_result(anal_result), absolute_error(abs_error),
          execution_time(0.0) {}
};

// Function declarations using MathFunction alias
double basicTrapezoidal(const MathFunction& f, double a, double b);
double basicSimpson(const MathFunction& f, double a, double b);

double trapezoidalNonRecursive(const MathFunction& f, double a, double b, int n_intervals);
double simpsonNonRecursive(const MathFunction& f, double a, double b, int n_intervals);

double adaptiveTrapezoidalRecursive(const MathFunction& f, double a, double b, double tol, int maxDepth, int depth);
double adaptiveSimpsonRecursive(const MathFunction& f, double a, double b, double tol, int maxDepth, int depth);

double adaptiveTrapezoidalNonRecursive(const MathFunction& f, double a, double b, double tolerance, int max_depth);
double simpsonNonAdaptiveRecursive(const MathFunction& f, double a, double b, double tol, int maxDepth, int depth);

#endif // INTEGRATION_METHODS_H
