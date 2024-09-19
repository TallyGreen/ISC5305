#include "grid3d_vector.h"
#include <iostream>
#include <stdexcept>

// Constructor: initializes the grid with dimensions nx, ny, nz
Grid2::Grid2(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    if (nx <= 0 || ny <= 0 || nz <= 0) {
        throw std::invalid_argument("Grid dimensions must be positive");
    }
    data.resize(nx, std::vector<std::vector<double>>(ny, std::vector<double>(nz, 0.0)));
}

// Destructor: nothing to clean up since std::vector handles its own memory
Grid2::~Grid2() {}

// Get the total number of elements in the grid
int Grid2::getSize() const {
    return nx * ny * nz;
}

// Get the memory usage in bytes (estimate)
int Grid2::getMemory() const {
    return sizeof(double) * getSize();
}

// Access an element in the grid (read-only version)
double Grid2::operator()(int i, int j, int k) const {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[i][j][k];
}

// Set the value of an element in the grid
void Grid2::set(int i, int j, int k, double value) {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    data[i][j][k] = value;
}

// Overload + operator to add two grids element-wise
Grid2 Grid2::operator+(const Grid2& other) {
    if (nx != other.nx || ny != other.ny || nz != other.nz) {
        throw std::invalid_argument("Grid dimensions must match for addition");
    }

    Grid2 result(nx, ny, nz);
    for (auto i = 0; i < nx; i++) {  // Using auto for loop variable
        for (auto j = 0; j < ny; j++) {  // Using auto for loop variable
            for (auto k = 0; k < nz; k++) {  // Using auto for loop variable
                result.data[i][j][k] = data[i][j][k] + other.data[i][j][k];
            }
        }
    }
    return result;
}

// Overload << operator to print the grid
std::ostream& operator<<(std::ostream& os, const Grid2& grid) {
    for (auto i = 0; i < grid.nx; i++) {  // Using auto for loop variable
        for (auto j = 0; j < grid.ny; j++) {  // Using auto for loop variable
            for (auto k = 0; k < grid.nz; k++) {  // Using auto for loop variable
                os << grid.data[i][j][k] << " ";
            }
            os << std::endl;
        }
        os << std::endl;
    }
    return os;
}
