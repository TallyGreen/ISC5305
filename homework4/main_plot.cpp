#include "function.h"
#include "solver_p.h"
#include <iostream>
#include <fstream> // To write iteration data to file
#include <memory>
#include <vector>

// Function to export the iteration data to a CSV file
void exportIterationData(const std::vector<double>& data, const std::string& filename) {
    std::ofstream outfile(filename);

    // Check if the file is open
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    // Export the iteration data
    for (size_t i = 0; i < data.size(); ++i) {
        outfile << i + 1 << "," << data[i] << std::endl;  // Write iteration number and root
    }

    // Check if the file was written successfully
    if (outfile.fail()) {
        std::cerr << "Error: Failed to write to file " << filename << ".\n";
    } else {
        std::cout << "Data successfully exported to " << filename << std::endl;
    }

    outfile.close();
}

int main() {
    // Cubic Function: f(x) = x^3 - 6x^2 + 11x - 8
    std::shared_ptr<Function<double>> cubicFunc = std::make_shared<CubicFunction<double>>();

    // Solver parameters
    double tolerance = 1e-6;
    int maxIterations = 1000;

    // Newton's Method for the cubic function with a better initial guess
    NewtonSolver<double> newtonSolver(tolerance, maxIterations);
    double newtonRoot = newtonSolver.computeRoot(*cubicFunc, 3.0); // Initial guess 3.0 (closer to the actual root)
    std::cout << "Newton Root: " << newtonRoot << " after " << newtonSolver.getFinalIteration() << " iterations.\n";
    exportIterationData(newtonSolver.iterationRoots, "newton_iteration_data.csv");

    // Secant Method for the cubic function (unchanged)
    SecantSolver<double> secantSolver(tolerance, maxIterations);
    double secantRoot = secantSolver.computeRoot(*cubicFunc, 1.5); // Initial guess 1.5
    std::cout << "Secant Root: " << secantRoot << " after " << secantSolver.getFinalIteration() << " iterations.\n";
    exportIterationData(secantSolver.iterationRoots, "secant_iteration_data.csv");

    return 0;
}
