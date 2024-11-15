#include <chrono>
#include "definitions.h"
#include "integration_methods.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <functional>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Integration {
protected:
    double a, b;
    bool isRecursive, isAdaptive;
    double timeTaken;
    double lastResult;

public:
    Integration(double lowerBound, double upperBound, bool recursive, bool adaptive)
        : a(lowerBound), b(upperBound), isRecursive(recursive), isAdaptive(adaptive), timeTaken(0), lastResult(0) {}

    virtual ~Integration() = default;
    
    double getA() const { return a; }
    double getB() const { return b; }

    virtual double integrate(CachedFunction& func) = 0;

    double operator()(CachedFunction& func) {
        auto start = std::chrono::high_resolution_clock::now();
        lastResult = integrate(func);
        auto end = std::chrono::high_resolution_clock::now();
        timeTaken = std::chrono::duration<double>(end - start).count();
        return lastResult;
    }

    double getTimeTaken() const { return timeTaken; }
    double getLastResult() const { return lastResult; }
};

class NonAdaptiveIntegration : public Integration {
private:
    int numIntervals;

public:
    NonAdaptiveIntegration(double lowerBound, double upperBound, bool recursive, int intervals)
        : Integration(lowerBound, upperBound, recursive, false), numIntervals(intervals) {}

    double integrate(CachedFunction& func) override {
        return simpsonNonRecursive(func, a, b, numIntervals);
    }
};

class AdaptiveIntegration : public Integration {
private:
    double tolerance;
    int maxDepth;

public:
    AdaptiveIntegration(double lowerBound, double upperBound, bool recursive, double tol, int maxDepth)
        : Integration(lowerBound, upperBound, recursive, true), tolerance(tol), maxDepth(maxDepth) {}

    double integrate(CachedFunction& func) override {
        return adaptiveSimpsonRecursive(func, a, b, tolerance, maxDepth, 0);
    }
};

class Trapezoidal : public Integration {
public:
    Trapezoidal(double a, double b, bool recursive, int numIntervals)
        : Integration(a, b, recursive, false), numIntervals(numIntervals) {}

    double integrate(CachedFunction& func) override {
        return trapezoidalNonRecursive(func, a, b, numIntervals);
    }

private:
    int numIntervals;
};

class AdaptiveTrapezoidal : public Integration {
public:
    AdaptiveTrapezoidal(double a, double b, bool recursive, double tol, int maxDepth)
        : Integration(a, b, recursive, true), tolerance(tol), maxDepth(maxDepth) {}

    double integrate(CachedFunction& func) override {
        return adaptiveTrapezoidalRecursive(func, a, b, tolerance, maxDepth, 0);
    }

private:
    double tolerance;
    int maxDepth;
};

class Simpson : public Integration {
public:
    Simpson(double a, double b, bool recursive, int numIntervals)
        : Integration(a, b, recursive, false), numIntervals(numIntervals) {}

    double integrate(CachedFunction& func) override {
        return simpsonNonRecursive(func, a, b, numIntervals);
    }

private:
    int numIntervals;
};

class AdaptiveSimpson : public Integration {
public:
    AdaptiveSimpson(double a, double b, bool recursive, double tol, int maxDepth)
        : Integration(a, b, recursive, true), tolerance(tol), maxDepth(maxDepth) {}

    double integrate(CachedFunction& func) override {
        return adaptiveSimpsonRecursive(func, a, b, tolerance, maxDepth, 0);
    }

private:
    double tolerance;
    int maxDepth;
};

// Overloading the `+` operator for cumulative integration results
double operator+(Integration& lhs, Integration& rhs) {
    if (lhs.getB() != rhs.getA()) {
        throw std::invalid_argument("Intervals are not contiguous: lhs.b must equal rhs.a.");
    }
    return lhs.getLastResult() + rhs.getLastResult();
}

class CumulativeIntegration {
    double totalResult;

public:
    CumulativeIntegration() : totalResult(0) {}

    CumulativeIntegration& operator+(Integration& integration) {
        totalResult += integration.getLastResult();
        return *this;
    }

    double getResult() const {
        return totalResult;
    }
};

// Test functions and analytical solutions
auto testSinX = [](double x) { return std::sin(x); };
auto testLogX = [](double x) { return std::log(x); };
auto testSin2X = [](double x) { return std::sin(2 * x); };

double integralSinX(double a, double b) { return -std::cos(b) + std::cos(a); }
double integralLogX(double a, double b) { return b * std::log(b) - b - (a * std::log(a) - a); }
double integralSin2X(double a, double b) { return -0.5 * std::cos(2 * b) + 0.5 * std::cos(2 * a); }

// Benchmark method
void benchmarkMethod(const MathFunction& analyticalFunction, Integration& integrator, 
                     double a, double b, double analyticalResult) {
    CachedFunction f(analyticalFunction);
    
    f.resetEvaluations();
    f.clearCache();

    auto start = std::chrono::high_resolution_clock::now();
    double numericalResult = integrator(f);
    auto end = std::chrono::high_resolution_clock::now();

    double executionTime = std::chrono::duration<double>(end - start).count();
    double absoluteError = std::abs(numericalResult - analyticalResult);

    std::cout << "Numerical result: " << numericalResult << std::endl;
    std::cout << "Analytical result: " << analyticalResult << std::endl;
    std::cout << "Absolute error: " << absoluteError << std::endl;
    std::cout << "Execution time: " << executionTime << " seconds" << std::endl;
    std::cout << "Function evaluations: " << f.getEvaluationCount() << std::endl;
}

// Benchmark Integration Methods
void benchmarkIntegrationMethods(std::vector<IntegrationResults>& results,
                                 const MathFunction& f,
                                 const std::string& methodName,
                                 const std::string& functionName,
                                 const std::string& cacheType,
                                 int intervals_or_depth,
                                 bool is_recursive,
                                 Integration& integrator,
                                 double analyticalResult) {
    CachedFunction cachedFunction(f);

    auto start = std::chrono::high_resolution_clock::now();
    double numericalResult = integrator(cachedFunction);
    auto end = std::chrono::high_resolution_clock::now();

    double executionTime = std::chrono::duration<double>(end - start).count();
    double absoluteError = std::abs(numericalResult - analyticalResult);

    IntegrationResults resultData(methodName, functionName, cacheType, intervals_or_depth,
                                  is_recursive, numericalResult, analyticalResult, absoluteError);
    resultData.execution_time = executionTime;

    results.push_back(resultData);
}

// Save results to CSV
void saveResultsToCSV(const std::vector<IntegrationResults>& results, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "method_name,function_name,cache_type,nb_intervals_or_max_depth,recursive,numerical_result,"
                "analytical_result,absolute_error,execution_time\n";
        for (const auto& result : results) {
            file << result.method_name << "," << result.function_name << "," << result.cache_type << ","
                 << result.nb_intervals_or_max_depth << "," << result.recursive << ","
                 << result.numerical_result << "," << result.analytical_result << ","
                 << result.absolute_error << "," << result.execution_time << "\n";
        }
        file.close();
    }
}

// Analyze results
void analyzeResults(const std::vector<IntegrationResults>& results) {
    double minError = std::numeric_limits<double>::max();
    double maxError = 0.0;
    double totalTime = 0.0;
    std::string bestMethod, worstMethod;

    for (const auto& result : results) {
        totalTime += result.execution_time;
        if (result.absolute_error < minError) {
            minError = result.absolute_error;
            bestMethod = result.method_name;
        }
        if (result.absolute_error > maxError) {
            maxError = result.absolute_error;
            worstMethod = result.method_name;
        }
    }

    std::cout << "Performance Analysis:\n";
    std::cout << "Total execution time: " << totalTime << " seconds\n";
    std::cout << "Most accurate method: " << bestMethod << " with error = " << minError << "\n";
    std::cout << "Least accurate method: " << worstMethod << " with error = " << maxError << "\n";
}

// Main function for benchmarking integration methods
int main() {
    double a = 0.0;
    double b = M_PI;

    Trapezoidal trapezoidalIntegrator(a, b, false, 100);
    AdaptiveSimpson adaptiveSimpsonIntegrator(a, b, true, 1e-8, 12);

    std::cout << "Benchmarking Trapezoidal on sin(x):" << std::endl;
    benchmarkMethod(testSinX, trapezoidalIntegrator, a, b, integralSinX(a, b));

    std::cout << "\nBenchmarking Adaptive Simpson on sin(x):" << std::endl;
    benchmarkMethod(testSinX, adaptiveSimpsonIntegrator, a, b, integralSinX(a, b));
    
    // Additional benchmarking
    std::vector<IntegrationResults> results;
    double new_a = 0.0001;
    double new_b = 3.14159;

    // Define integration instances
    Trapezoidal trapezoidalIntegrator1(new_a, new_b, false, 10);
    Simpson simpsonIntegrator2(new_a, new_b, false, 20);
    AdaptiveTrapezoidal adaptiveTrapezoidalIntegrator3(new_a, new_b, true, 1e-5, 25);
    AdaptiveSimpson adaptiveSimpsonIntegrator4(new_a, new_b, true, 1e-5, 25);

    double analyticalResultSinX = integralSinX(new_a, new_b);
    double analyticalResultLogX = integralLogX(new_a, new_b);
    double analyticalResultSin2X = integralSin2X(new_a, new_b);

    benchmarkIntegrationMethods(results, testSinX, "Trapezoidal", "sin(x)", "none", 10, false, trapezoidalIntegrator1, analyticalResultSinX);
    benchmarkIntegrationMethods(results, testSinX, "Trapezoidal", "sin(x)", "fast", 20, false, trapezoidalIntegrator1, analyticalResultSinX);
    benchmarkIntegrationMethods(results, testSinX, "Trapezoidal", "sin(x)", "slow", 30, false, trapezoidalIntegrator1, analyticalResultSinX);

    benchmarkIntegrationMethods(results, testLogX, "Simpson", "log(x)", "none", 10, false, simpsonIntegrator2, analyticalResultLogX);
    benchmarkIntegrationMethods(results, testLogX, "Simpson", "log(x)", "fast", 20, false, simpsonIntegrator2, analyticalResultLogX);
    benchmarkIntegrationMethods(results, testLogX, "Simpson", "log(x)", "slow", 30, false, simpsonIntegrator2, analyticalResultLogX);

    benchmarkIntegrationMethods(results, testSin2X, "AdaptiveTrapezoidal", "sin(2x)", "none", 5, true, adaptiveTrapezoidalIntegrator3, analyticalResultSin2X);
    benchmarkIntegrationMethods(results, testSin2X, "AdaptiveTrapezoidal", "sin(2x)", "fast", 15, true, adaptiveTrapezoidalIntegrator3, analyticalResultSin2X);
    benchmarkIntegrationMethods(results, testSin2X, "AdaptiveTrapezoidal", "sin(2x)", "slow", 25, true, adaptiveTrapezoidalIntegrator3, analyticalResultSin2X);

    benchmarkIntegrationMethods(results, testSin2X, "AdaptiveSimpson", "sin(2x)", "none", 5, true, adaptiveSimpsonIntegrator4, analyticalResultSin2X);
    benchmarkIntegrationMethods(results, testSin2X, "AdaptiveSimpson", "sin(2x)", "fast", 15, true, adaptiveSimpsonIntegrator4, analyticalResultSin2X);
    benchmarkIntegrationMethods(results, testSin2X, "AdaptiveSimpson", "sin(2x)", "slow", 25, true, adaptiveSimpsonIntegrator4, analyticalResultSin2X);

    saveResultsToCSV(results, "benchmark_results.csv");

    analyzeResults(results);

    return 0;
}
