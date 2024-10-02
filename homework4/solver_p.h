#ifndef SOLVER_H
#define SOLVER_H

#include <cmath>
#include <iostream>
#include <vector>
#include "function.h"

// Base Solver class for Newton and Secant solvers
template <typename T>
class Solver {
protected:
    int finalIteration;   // Number of iterations completed
    double tolerance;     // Tolerance level to stop iteration
    int maxIterations;    // Maximum allowed iterations

public:
    Solver(double tolerance_, int maxIterations_)
        : finalIteration(0), tolerance(tolerance_), maxIterations(maxIterations_) {}

    virtual ~Solver() {}

    // Base function to compute the root (to be overridden by derived classes)
    virtual T computeRoot(Function<T>& func, T x0) = 0;

    // Function to return the number of iterations completed
    int getFinalIteration() { return finalIteration; }
};

// Newton Solver class
template <typename T>
class NewtonSolver : public Solver<T> {
public:
    std::vector<T> iterationRoots;  // To store roots at each iteration

    NewtonSolver(double tolerance_, int maxIterations_)
        : Solver<T>(tolerance_, maxIterations_) {}

    // Newton's method to compute the root
    T computeRoot(Function<T>& func, T x0) override {
        T x = x0;
        for (int i = 0; i < this->maxIterations; ++i) {
            T fx = func(x);
            T dfx = func.fp(x); // Derivative

            // Safeguard: If the derivative is too small, we could overshoot or stagnate
            if (std::fabs(dfx) < 1e-12) {
                std::cerr << "Derivative too small in iteration " << i << ", stopping.\n";
                return x;
            }

            // Compute next root using Newton's method
            T next_x = x - fx / dfx;

            // Safeguard: Prevent large steps that could lead to erratic behavior
            if (std::fabs(next_x - x) > 100) {
                std::cerr << "Large step detected in iteration " << i << ", limiting the step.\n";
                next_x = x + (next_x - x) / 10;  // Limit large steps
            }

            iterationRoots.push_back(next_x);  // Log the computed root after each iteration

            // Check if the current root is close enough (within tolerance)
            if (std::fabs(next_x - x) < this->tolerance) {
                this->finalIteration = i;
                return next_x;  // Root found
            }

            x = next_x;  // Update the current root for the next iteration
        }

        std::cerr << "Newton's method did not converge after " << this->maxIterations << " iterations.\n";
        this->finalIteration = this->maxIterations;
        return x;
    }
};


// Secant Solver class
template <typename T>
class SecantSolver : public Solver<T> {
public:
    std::vector<T> iterationRoots;  // To store roots at each iteration

    SecantSolver(double tolerance_, int maxIterations_)
        : Solver<T>(tolerance_, maxIterations_) {}

    // Secant method to compute the root with two initial guesses
    T computeRoot(Function<T>& func, T x0, T x1) {
        for (int i = 0; i < this->maxIterations; ++i) {
            T fx0 = func(x0);
            T fx1 = func(x1);

            // Prevent division by zero or too small a difference
            if (std::fabs(fx1 - fx0) < 1e-12) {
                std::cerr << "Secant method failed: small difference between f(x1) and f(x0) in iteration " << i << ".\n";
                return std::nan("");
            }

            if (std::fabs(fx1) < this->tolerance) {
                this->finalIteration = i;
                iterationRoots.push_back(x1);  // Save the final root
                return x1; // Root found
            }

            // Secant method formula
            T x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);

            // Update values for the next iteration
            x0 = x1;
            x1 = x2;

            iterationRoots.push_back(x1);  // Log the computed root after each iteration
        }

        std::cerr << "Secant method did not converge after " << this->maxIterations << " iterations.\n";
        this->finalIteration = this->maxIterations;
        return x1;
    }

    // Overriding the single argument version of computeRoot for compatibility
    T computeRoot(Function<T>& func, T x0) override {
        return computeRoot(func, x0, x0 + 1.0);
    }
};

#endif
