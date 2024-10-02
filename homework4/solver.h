#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <cmath>
#include "function.h"

template <typename T>
class Solver {
protected:
    int finalIteration;
    double tolerance;
    int maxIterations;

public:
    Solver(double tolerance_, int maxIterations_)
        : finalIteration(0), tolerance(tolerance_), maxIterations(maxIterations_) {}

    virtual ~Solver() {}
    
    // Base computeRoot function signature
    virtual T computeRoot(Function<T>& func, T x0) = 0;
    
    int getFinalIteration() { return finalIteration; }
};

// Newton Solver class
template <typename T>
class NewtonSolver : public Solver<T> {
public:
    NewtonSolver(double tolerance_, int maxIterations_) : Solver<T>(tolerance_, maxIterations_) {}

    // Newton's method to compute the root
    T computeRoot(Function<T>& func, T x0) override {
        T x = x0;
        for (int i = 0; i < this->maxIterations; ++i) {
            T fx = func(x);
            T dfx = func.fp(x); // Derivative

            if (std::fabs(fx) < this->tolerance) {
                this->finalIteration = i;
                return x; // Root found
            }

            // Update x using Newton's formula
            x = x - fx / dfx;
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
    SecantSolver(double tolerance_, int maxIterations_) : Solver<T>(tolerance_, maxIterations_) {}

    // Internal version of computeRoot for Secant method with two initial guesses
    T computeRoot(Function<T>& func, T x0, T x1) {
        for (int i = 0; i < this->maxIterations; ++i) {
            T fx0 = func(x0);
            T fx1 = func(x1);

            // Prevent division by zero or too small a difference
            if (std::fabs(fx1 - fx0) < 1e-12) {
                std::cerr << "Secant method failed: small difference between f(x1) and f(x0) in iteration " << i << ".\n";
                return std::nan("");
            }

            // If function value is already close to zero, return the root
            if (std::fabs(fx1) < this->tolerance) {
                this->finalIteration = i;
                return x1; // Root found
            }

            // Secant method formula
            T x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);

            // Update values for the next iteration
            x0 = x1;
            x1 = x2;
        }

        std::cerr << "Secant method did not converge after " << this->maxIterations << " iterations.\n";
        this->finalIteration = this->maxIterations;
        return std::nan("");
    }

    // Overriding the single argument version of computeRoot for compatibility
    T computeRoot(Function<T>& func, T x0) override {
        // Use x0 and a default guess of x0 + 0.5 for the Secant method
        return computeRoot(func, x0, x0 + 0.5);
    }
};


#endif
