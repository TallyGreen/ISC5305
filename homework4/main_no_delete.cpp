#include "function.h"
#include "solver.h"
#include <iostream>
#include <memory>
#include <vector>

int main() {
    // Collection of functions managed by shared_ptr
    std::vector<std::shared_ptr<Function<double>>> functions = {
        std::make_shared<SinFunction<double>>(),
        std::make_shared<CubicFunction<double>>(),
        std::make_shared<LogQuadraticFunction<double>>()
    };

    // Solver parameters
    struct SolverParams {
        double tolerance;
        int maxIterations;
    };

    std::vector<SolverParams> params = {
        {0.01, 100},
        {0.001, 500},
        {1e-6, 1000}
    };

    // Iterate through each function, solver, and parameter set
    for (const auto& func : functions) {
        for (const auto& p : params) {
            // Use shared_ptr for NewtonSolver
            std::shared_ptr<Solver<double>> newtonSolver = std::make_shared<NewtonSolver<double>>(p.tolerance, p.maxIterations);
            std::cout << "Using Newton's Method for function: " << func->name << std::endl;
            double newtonRoot = newtonSolver->computeRoot(*func, 1.0); // Initial guess 1.0
            std::cout << "Newton Root: " << newtonRoot << " after " << newtonSolver->getFinalIteration() << " iterations.\n";
            std::cout << "Newton Verification (Error): " << func->verify(newtonRoot) << "\n";

            // Use shared_ptr for SecantSolver
            std::shared_ptr<Solver<double>> secantSolver = std::make_shared<SecantSolver<double>>(p.tolerance, p.maxIterations);
            std::cout << "Using Secant Method for function: " << func->name << std::endl;
            double secantRoot = secantSolver->computeRoot(*func, 1.5); // Single initial guess
            std::cout << "Secant Root: " << secantRoot << " after " << secantSolver->getFinalIteration() << " iterations.\n";
            std::cout << "Secant Verification (Error): " << func->verify(secantRoot) << "\n";
        }
    }

    return 0;
}
