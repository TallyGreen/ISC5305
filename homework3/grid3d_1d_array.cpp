#include "grid3d_1d_array.h"
#include <iostream>
#include <stdexcept>

// Constructor
Grid1::Grid1(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    data = new double[nx * ny * nz];  // Allocate memory
    for (auto i = 0; i < nx * ny * nz; i++) {  // Using auto for iterator
        data[i] = 0.0;  // Initialize grid to 0
    }
}

// Destructor
Grid1::~Grid1() {
    delete[] data;  // Deallocate memory
}

// Get total number of elements
int Grid1::getSize() const {
    return nx * ny * nz;
}

// Get memory usage in bytes
int Grid1::getMemory() const {
    return sizeof(double) * getSize();
}

// Access element using 3D indices (const version)
double Grid1::operator()(int i, int j, int k) const {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    auto index = i * (ny * nz) + j * nz + k;  // Using auto for index calculation
    return data[index];
}

// Set value of an element at (i, j, k)
void Grid1::set(int i, int j, int k, double value) {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    auto index = i * (ny * nz) + j * nz + k;  // Using auto for index calculation
    data[index] = value;
}

// Overload + operator to add two grids
Grid1 Grid1::operator+(const Grid1& grid) {
    if (nx != grid.nx || ny != grid.ny || nz != grid.nz) {
        throw std::invalid_argument("Grid dimensions must match for addition");
    }

    Grid1 result(nx, ny, nz);
    for (auto i = 0; i < nx * ny * nz; i++) {  // Using auto for iterator
        result.data[i] = data[i] + grid.data[i];
    }
    return result;
}

// Overload << operator for output
std::ostream& operator<<(std::ostream& os, const Grid1& grid) {
    for (auto i = 0; i < grid.nx; i++) {  // Using auto for iterator
        for (auto j = 0; j < grid.ny; j++) {  // Using auto for iterator
            for (auto k = 0; k < grid.nz; k++) {  // Using auto for iterator
                os << grid(i, j, k) << " ";
            }
            os << std::endl;
        }
        os << std::endl;
    }
    return os;
}
