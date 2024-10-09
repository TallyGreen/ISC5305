#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include "brain_mesh.h"

// Function to save a vector of values to a file
template <typename T>
void saveVector(const std::string& fileName, const std::vector<T>& values) {
    std::ofstream outFile(fileName);
    if (!outFile) {
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return;
    }

    for (const auto& value : values) {
        outFile << std::setprecision(14) << value << std::endl;
    }
    outFile.close();
    std::cout << "Data saved to " << fileName << std::endl;
}

// Function to compare floating-point numbers with a tolerance
bool isClose(double a, double b, double tolerance = 1e-6) {
    return std::fabs(a - b) < tolerance;
}

int main() {
    bool test_code = true; // Set to true to run the test code
    std::cout << std::setprecision(14) << std::endl;

    // Test code section
    if (test_code) {
        // Create a BrainMesh instance for testing
        BrainMesh<double, long> testBrain("test_brain");

        // Manually input vertices for a right-angled triangle
        testBrain.getVertices().push_back({0.0, 0.0, 0.0}); // Vertex 0
        testBrain.getVertices().push_back({1.0, 0.0, 0.0}); // Vertex 1
        testBrain.getVertices().push_back({0.0, 1.0, 0.0}); // Vertex 2

        // Manually input a single triangle
        testBrain.getTriangles().push_back({0, 1, 2}); // Triangle 0

        // Debug: Check the number of vertices and triangles loaded
        std::cout << "Vertices loaded: " << testBrain.getVertices().size() << std::endl;
        std::cout << "Triangles loaded: " << testBrain.getTriangles().size() << std::endl;

        // Calculate the total surface area
        double totalArea = testBrain.getTotalArea();
        double expectedTotalArea = 0.5; // Area of a right-angled triangle with base 1 and height 1
        std::cout << "Calculated total area: " << totalArea << std::endl;
        std::cout << "Expected total area: " << expectedTotalArea << std::endl;
        assert(isClose(totalArea, expectedTotalArea));
        std::cout << "Test passed: Total area matches expected value." << std::endl;
    }}