#ifndef BRAIN_MESH_H
#define BRAIN_MESH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <cmath>
#include <string>
#include <iomanip>
#include <algorithm>

// Define the template class for BrainMesh
template <typename T, typename INT>
class BrainMesh {
private:
    // Store the vertices as 3D coordinates
    std::vector<std::array<T, 3>> vertices;
    // Store the triangle vertex indices
    std::vector<std::array<INT, 3>> triangles;
    // Store the area of each triangle
    std::vector<T> triangleAreas;
    // Store the area around each vertex
    std::vector<T> vertexAreas;
    // Store the lengths of edges of the triangles
    std::vector<T> edgeLengths;
    // Total surface area of the mesh
    T totalArea;
    int nbPoints;  // Number of points (vertices)
    int nbTriangles;  // Number of triangles
    std::string name;  // Name or identifier for the mesh

public:
    // Constructor
    BrainMesh(const std::string& name);

    // Destructor
    ~BrainMesh() {}

    // Method to read data from a VTK file
    void readData(const std::string& fileName);

    // Calculate the total area of the mesh
    T getTotalArea();

    // Compute the area around each vertex
    void computeVertexAreas();

    // Get vertex areas
    std::vector<T> getVertexAreas();

    // Get triangle areas
    std::vector<T> getTriangleAreas();

    // Get edge lengths
    std::vector<T> getEdgeLengths();

    // Save vertex areas to a file
    void saveVertexAreas(const std::string& fileName);
    
    // Getter for vertices (const version)
    const std::vector<std::array<T, 3>>& getVertices() const {
        return vertices;
    }

    // Getter for vertices (non-const version)
    std::vector<std::array<T, 3>>& getVertices() {
        return vertices;
    }

    // Getter for triangles (const version)
    const std::vector<std::array<INT, 3>>& getTriangles() const {
        return triangles;
    }

    // Getter for triangles (non-const version)
    std::vector<std::array<INT, 3>>& getTriangles() {
        return triangles;
    }

private:
    // Calculate the area of a triangle given its indices
    T getTriangleArea(const std::array<INT, 3>& triangle);
};

// Include the template implementations
#include "brain_mesh.hxx"

#endif // BRAIN_MESH_H
