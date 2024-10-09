#ifndef BRAIN_MESH_HXX
#define BRAIN_MESH_HXX

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

// Constructor for the BrainMesh class
template <typename T, typename INT>
BrainMesh<T, INT>::BrainMesh(const std::string& name) : name(name), totalArea(0), nbPoints(0), nbTriangles(0) {}

// Method to read data from a VTK file
template <typename T, typename INT>
void BrainMesh<T, INT>::readData(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return;
    }

    std::string line;
    int lineCount = 0;

    // Read vertices (skipping the header lines)
    while (std::getline(file, line) && lineCount < 191730) {
        lineCount++;
        if (lineCount <= 5) continue;  // Skip header lines

        std::istringstream iss(line);
        T x, y, z;
        iss >> x >> y >> z;
        vertices.push_back({x, y, z});
    }

    // Read triangles
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int indicator;
        INT v1, v2, v3;
        iss >> indicator >> v1 >> v2 >> v3;
        if (indicator == 3) {
            triangles.push_back({v1, v2, v3});
        }
    }

    nbPoints = vertices.size();
    nbTriangles = triangles.size();

    std::cout << "Loaded " << nbPoints << " vertices and " << nbTriangles << " triangles." << std::endl;
}

// Calculate the area of a triangle using its vertex indices
template <typename T, typename INT>
T BrainMesh<T, INT>::getTriangleArea(const std::array<INT, 3>& triangle) {
    const auto& v1 = vertices[triangle[0]];
    const auto& v2 = vertices[triangle[1]];
    const auto& v3 = vertices[triangle[2]];

    std::array<T, 3> r12 = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
    std::array<T, 3> r13 = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};

    // Compute the cross product
    std::array<T, 3> cross = {
        r12[1] * r13[2] - r12[2] * r13[1],
        r12[2] * r13[0] - r12[0] * r13[2],
        r12[0] * r13[1] - r12[1] * r13[0]
    };

    // Compute the magnitude of the cross product vector to get the area
    T area = 0.5 * std::sqrt(cross[0] * cross[0] + cross[1] * cross[1] + cross[2] * cross[2]);
    return area;
}

// Calculate the total surface area of the brain mesh
template <typename T, typename INT>
T BrainMesh<T, INT>::getTotalArea() {
    totalArea = 0;
    triangleAreas.clear();
    for (const auto& triangle : triangles) {
        T area = getTriangleArea(triangle);
        triangleAreas.push_back(area);
        totalArea += area;
    }
    return totalArea;
}

// Compute the area around each vertex
template <typename T, typename INT>
void BrainMesh<T, INT>::computeVertexAreas() {
    vertexAreas.resize(vertices.size(), 0);
    for (size_t i = 0; i < triangles.size(); ++i) {
        const auto& triangle = triangles[i];
        T area = triangleAreas[i];

        vertexAreas[triangle[0]] += area / 3.0;
        vertexAreas[triangle[1]] += area / 3.0;
        vertexAreas[triangle[2]] += area / 3.0;
    }
}

// Get vertex areas
template <typename T, typename INT>
std::vector<T> BrainMesh<T, INT>::getVertexAreas() {
    return vertexAreas;
}

// Get triangle areas
template <typename T, typename INT>
std::vector<T> BrainMesh<T, INT>::getTriangleAreas() {
    return triangleAreas;
}

// Get edge lengths
template <typename T, typename INT>
std::vector<T> BrainMesh<T, INT>::getEdgeLengths() {
    edgeLengths.clear();

    for (const auto& triangle : triangles) {
        const auto& v1 = vertices[triangle[0]];
        const auto& v2 = vertices[triangle[1]];
        const auto& v3 = vertices[triangle[2]];

        // Calculate lengths of each edge of the triangle
        T length1 = std::sqrt(std::pow(v2[0] - v1[0], 2) + std::pow(v2[1] - v1[1], 2) + std::pow(v2[2] - v1[2], 2));
        T length2 = std::sqrt(std::pow(v3[0] - v2[0], 2) + std::pow(v3[1] - v2[1], 2) + std::pow(v3[2] - v2[2], 2));
        T length3 = std::sqrt(std::pow(v3[0] - v1[0], 2) + std::pow(v3[1] - v1[1], 2) + std::pow(v3[2] - v1[2], 2));

        // Store each length
        edgeLengths.push_back(length1);
        edgeLengths.push_back(length2);
        edgeLengths.push_back(length3);
    }

    return edgeLengths;
}

// Save vertex areas to a file
template <typename T, typename INT>
void BrainMesh<T, INT>::saveVertexAreas(const std::string& fileName) {
    std::ofstream outFile(fileName);
    if (!outFile) {
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return;
    }

    for (const auto& area : vertexAreas) {
        outFile << std::setprecision(14) << area << std::endl;
    }

    outFile.close();
    std::cout << "Vertex areas saved to " << fileName << std::endl;
}

#endif // BRAIN_MESH_HXX
