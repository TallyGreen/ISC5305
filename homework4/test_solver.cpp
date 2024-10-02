#include "function.h"
#include "solver.h"
#include <iostream>
#include <memory>
#include <cassert>

void testNewtonsMethod() {
    // Testing with Newton's Method
    std::cout << "Testing Newton's Method:" << std::endl;

    // Create instances of functions
    std::shared_ptr<Function<double>> cubicFunc = std::make_shared<CubicFunction<double>>();
    std::shared_ptr<Function<double>> sinFunc = std::make_shared<SinFunction<double>>();
    std::shared_ptr<Function<double>> logQuadFunc = std::make_shared<LogQuadraticFunction<double>>();

    // Create Newton solvers
    NewtonSolver<double> newtonSolver1(1e-6, 100);
    NewtonSolver<double> newtonSolver2(1e-6, 100);
    NewtonSolver<double> newtonSolver3(1e-6, 100);

    // Solve for roots
    double cubicRoot = newtonSolver1.computeRoot(*cubicFunc, 2.0); // initial guess 2.0
    double sinRoot = newtonSolver2.computeRoot(*sinFunc, 1.0); // initial guess 1.0
    double logQuadRoot = newtonSolver3.computeRoot(*logQuadFunc, 2.0); // initial guess 2.0

    // Verify the results (asserting that the error should be near 0)
    std::cout << "Cubic Function Root (Newton): " << cubicRoot << " | Verification Error: " << cubicFunc->verify(cubicRoot) << std::endl;
    assert(cubicFunc->verify(cubicRoot) < 1e-6);  // Check if error is very small

    std::cout << "Sin Function Root (Newton): " << sinRoot << " | Verification Error: " << sinFunc->verify(sinRoot) << std::endl;
    assert(sinFunc->verify(sinRoot) < 1e-6);

    std::cout << "Log-Quadratic Function Root (Newton): " << logQuadRoot << " | Verification Error: " << logQuadFunc->verify(logQuadRoot) << std::endl;
    assert(logQuadFunc->verify(logQuadRoot) < 1e-6);

    std::cout << "All Newton's Method tests passed.\n" << std::endl;
}

void testSecantMethod() {
    // Testing with Secant Method
    std::cout << "Testing Secant Method:" << std::endl;

    // Create instances of functions
    std::shared_ptr<Function<double>> cubicFunc = std::make_shared<CubicFunction<double>>();
    std::shared_ptr<Function<double>> sinFunc = std::make_shared<SinFunction<double>>();
    std::shared_ptr<Function<double>> logQuadFunc = std::make_shared<LogQuadraticFunction<double>>();

    // Create Secant solvers
    SecantSolver<double> secantSolver1(1e-6, 100);
    SecantSolver<double> secantSolver2(1e-6, 100);
    SecantSolver<double> secantSolver3(1e-6, 100);

    // Solve for roots
    double cubicRoot = secantSolver1.computeRoot(*cubicFunc, 1.5); // initial guess 1.5
    double sinRoot = secantSolver2.computeRoot(*sinFunc, 1.0); // initial guess 1.0
    double logQuadRoot = secantSolver3.computeRoot(*logQuadFunc, 1.5); // initial guess 1.5

    // Verify the results (asserting that the error should be near 0)
    std::cout << "Cubic Function Root (Secant): " << cubicRoot << " | Verification Error: " << cubicFunc->verify(cubicRoot) << std::endl;
    assert(cubicFunc->verify(cubicRoot) < 1e-6);  // Check if error is very small

    std::cout << "Sin Function Root (Secant): " << sinRoot << " | Verification Error: " << sinFunc->verify(sinRoot) << std::endl;
    assert(sinFunc->verify(sinRoot) < 1e-6);

    std::cout << "Log-Quadratic Function Root (Secant): " << logQuadRoot << " | Verification Error: " << logQuadFunc->verify(logQuadRoot) << std::endl;
    assert(logQuadFunc->verify(logQuadRoot) < 1e-6);

    std::cout << "All Secant Method tests passed.\n" << std::endl;
}

int main() {
    testNewtonsMethod();
    testSecantMethod();
    return 0;
}
