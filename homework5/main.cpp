#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib>
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

int main() {
    bool test_code = false;
    std::cout << std::setprecision(14) << std::endl;

    if (test_code) {
        exit(0);
    }

    // Define BrainMesh instances for float and double precision
    BrainMesh<float, long> brainFloat("brain_float");
    BrainMesh<double, long> brainDouble("brain_double");

    // Read data from the VTK file for both instances
    brainFloat.readData("Cort_lobe_poly.vtk");
    brainDouble.readData("Cort_lobe_poly.vtk");

    // Calculate total surface area in float precision
    float totalAreaFloat = brainFloat.getTotalArea();
    std::cout << "Total brain surface area (float): " << totalAreaFloat << std::endl;

    // Calculate total surface area in double precision
    double totalAreaDouble = brainDouble.getTotalArea();
    std::cout << "Total brain surface area (double): " << totalAreaDouble << std::endl;

    // Compute vertex areas in double precision
    brainDouble.computeVertexAreas();
    std::vector<double> vertexAreas = brainDouble.getVertexAreas();

    // Save the vertex areas to a file named "vertex_areas.txt"
    brainDouble.saveVertexAreas("vertex_areas.txt");

    // Save the triangle areas to a file named "triangle_areas.txt"
    std::vector<double> triangleAreas = brainDouble.getTriangleAreas();
    saveVector("triangle_areas.txt", triangleAreas);

    // Save the edge lengths to a file named "edge_lengths.txt"
    std::vector<double> edgeLengths = brainDouble.getEdgeLengths();
    saveVector("edge_lengths.txt", edgeLengths);

    // Sum the vertex areas
    double sumVertexAreas = 0;
    for (auto area : vertexAreas) {
        sumVertexAreas += area;
    }
    std::cout << "Sum of vertex areas: " << sumVertexAreas << std::endl;

    return 0;
}
