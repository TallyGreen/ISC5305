// integration_utils.cpp
#include "integration_methods.h"
#include <unordered_map>
#include <functional>
#include <vector>
#include <cmath>
using MathFunction = std::function<double(double)>;

// Basic Trapezoidal rule
double basicTrapezoidal(const MathFunction& f, double a, double b) {
    return 0.5 * (b - a) * (f(a) + f(b));
}

// Basic Simpson's rule
double basicSimpson(const MathFunction& f, double a, double b) {
    double h = (b - a) / 2;
    double mid = (a + b) / 2;
    return (h / 3) * (f(a) + 4 * f(mid) + f(b));
}

// Non-recursive trapezoidal rule
double trapezoidalNonRecursive(const MathFunction& f, double a, double b, int n_intervals) {
    double h = (b - a) / n_intervals;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n_intervals; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return h * sum;
}

// Non-recursive Simpson's rule
double simpsonNonRecursive(const MathFunction& f, double a, double b, int n_intervals) {
    int n = n_intervals;
    if (n % 2 != 0) n++;

    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += (i % 2 == 0) ? 2 * f(x) : 4 * f(x);
    }

    return h * sum / 3;
}

// Recursive adaptive trapezoidal rule
double adaptiveTrapezoidalRecursive(const MathFunction& f, double a, double b, double tol, int maxDepth, int depth) {
    if (depth >= maxDepth) {
        return basicTrapezoidal(f, a, b);
    }

    double c = (a + b) / 2;
    double one_trap = basicTrapezoidal(f, a, b);
    double two_trap = basicTrapezoidal(f, a, c) + basicTrapezoidal(f, c, b);
    double error = std::abs(two_trap - one_trap);

    if (error < tol) {
        return two_trap;
    }

    return adaptiveTrapezoidalRecursive(f, a, c, tol / 2, maxDepth, depth + 1) +
           adaptiveTrapezoidalRecursive(f, c, b, tol / 2, maxDepth, depth + 1);
}

// Recursive adaptive Simpson's rule
double adaptiveSimpsonRecursive(const MathFunction& f, double a, double b, double tol, int maxDepth, int depth) {
    if (depth >= maxDepth) {
        return basicSimpson(f, a, b);
    }

    double c = (a + b) / 2;
    double fa = f(a), fb = f(b), fc = f(c);
    double whole = (b - a) * (fa + 4 * fc + fb) / 6;
    double left = (c - a) * (fa + 4 * f((a + c) / 2) + fc) / 6;
    double right = (b - c) * (fc + 4 * f((c + b) / 2) + fb) / 6;
    double error = std::abs(left + right - whole);

    if (error < tol) {
        return left + right;
    }

    return adaptiveSimpsonRecursive(f, a, c, tol / 2, maxDepth, depth + 1) +
           adaptiveSimpsonRecursive(f, c, b, tol / 2, maxDepth, depth + 1);
}

// Non-recursive adaptive trapezoidal rule
double adaptiveTrapezoidalNonRecursive(const MathFunction& f, double a, double b, double tolerance, int max_depth) {
    std::vector<Interval> intervals;
    double total_area = 0.0;

    double fa = f(a), fb = f(b);
    intervals.push_back({a, b, fa, fb, 0.5 * (b - a) * (fa + fb), 0});

    while (!intervals.empty()) {
        Interval interval = intervals.back();
        intervals.pop_back();

        if (interval.depth >= max_depth) {
            total_area += interval.area;
            continue;
        }

        double mid = (interval.a + interval.b) / 2;
        double f_mid = f(mid);

        Interval left = {interval.a, mid, interval.fa, f_mid, 0.5 * (mid - interval.a) * (interval.fa + f_mid), interval.depth + 1};
        Interval right = {mid, interval.b, f_mid, interval.fb, 0.5 * (interval.b - mid) * (f_mid + interval.fb), interval.depth + 1};

        double error = std::abs(left.area + right.area - interval.area);

        if (error < tolerance) {
            total_area += left.area + right.area;
        } else {
            intervals.push_back(right);
            intervals.push_back(left);
        }
    }

    return total_area;
}

// Non-recursive adaptive Simpson's rule
double simpsonNonAdaptiveRecursive(const MathFunction& f, double a, double b, double tol, int maxDepth, int depth) {
    if (depth >= maxDepth) {
        return basicSimpson(f, a, b);
    }

    double c = (a + b) / 2;
    double fa = f(a), fb = f(b), fc = f(c);
    double whole = (b - a) * (fa + 4 * fc + fb) / 6;
    double left = (c - a) * (fa + 4 * f((a + c) / 2) + fc) / 6;
    double right = (b - c) * (fc + 4 * f((c + b) / 2) + fb) / 6;
    double error = std::abs(left + right - whole);

    if (error < tol) {
        return left + right;
    }

    return simpsonNonAdaptiveRecursive(f, a, c, tol / 2, maxDepth, depth + 1) +
           simpsonNonAdaptiveRecursive(f, c, b, tol / 2, maxDepth, depth + 1);
}
