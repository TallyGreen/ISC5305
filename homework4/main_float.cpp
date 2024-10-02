#include "function.h"
#include "solver.h"
#include <iostream>
#include <memory>
#include <vector>

int main() {
    // Collection of functions specialized for floats
    std::vector<std::shared_ptr<Function<float>>> functions = {
        std::make_shared<SinFunction<float>>(),
        std::make_shared<CubicFunction<float>>(),
        std::make_shared<LogQuadraticFunction<float>>()
    };

    // Different solver parameters
    struct SolverParams {
        float tolerance;
        int maxIterations;
    };

    std::vector<SolverParams> params = {
        {0.01f, 100},
        {0.001f, 500},
        {1e-6f, 1000}
    };

    // Iterating through each function, each solver, and each parameter set
    for (const auto& func : functions) {
        for (const auto& p : params) {
            std::shared_ptr<Solver<float>> newtonSolver = std::make_shared<NewtonSolver<float>>(p.tolerance, p.maxIterations);
            std::cout << "Using Newton's Method for function: " << func->name << std::endl;
            float newtonRoot = newtonSolver->computeRoot(*func, 1.0f); // Initial guess 1.0
            std::cout << "Newton Root: " << newtonRoot << " after " << newtonSolver->getFinalIteration() << " iterations.\n";
            std::cout << "Newton Verification (Error): " << func->verify(newtonRoot) << "\n";

            std::shared_ptr<Solver<float>> secantSolver = std::make_shared<SecantSolver<float>>(p.tolerance, p.maxIterations);
            std::cout << "Using Secant Method for function: " << func->name << std::endl;
            float secantRoot = secantSolver->computeRoot(*func, 1.5f); // Single initial guess
            std::cout << "Secant Root: " << secantRoot << " after " << secantSolver->getFinalIteration() << " iterations.\n";
            std::cout << "Secant Verification (Error): " << func->verify(secantRoot) << "\n";
        }
    }

    return 0;
}
