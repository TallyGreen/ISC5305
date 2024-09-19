#include "grid3d_new.h"
#include <iostream>
#include <stdexcept>

// Constructor: Allocates memory for the 3D array using `new`
Grid3::Grid3(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    if (nx <= 0 || ny <= 0 || nz <= 0) {
        throw std::invalid_argument("Grid dimensions must be positive");
    }

    data = new double**[nx];  // Allocate 1st dimension
    for (auto i = 0; i < nx; ++i) {  // Using auto for loop variable
        data[i] = new double*[ny];  // Allocate 2nd dimension
        for (auto j = 0; j < ny; ++j) {  // Using auto for loop variable
            data[i][j] = new double[nz];  // Allocate 3rd dimension
            for (auto k = 0; k < nz; ++k) {  // Using auto for loop variable
                data[i][j][k] = 0.0;  // Initialize all values to 0.0
            }
        }
    }
}

// Destructor: Frees the dynamically allocated memory
Grid3::~Grid3() {
    for (auto i = 0; i < nx; ++i) {  // Using auto for loop variable
        for (auto j = 0; j < ny; ++j) {  // Using auto for loop variable
            delete[] data[i][j];  // Deallocate 3rd dimension
        }
        delete[] data[i];  // Deallocate 2nd dimension
    }
    delete[] data;  // Deallocate 1st dimension
}

// Get the total number of elements in the grid
int Grid3::getSize() const {
    return nx * ny * nz;
}

// Get the memory usage in bytes
int Grid3::getMemory() const {
    return sizeof(double) * getSize();
}

// Access an element in the grid (read-only version)
double Grid3::operator()(int i, int j, int k) const {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[i][j][k];
}

// Set the value of an element in the grid
void Grid3::set(int i, int j, int k, double value) {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    data[i][j][k] = value;
}

// Overload + operator to add two grids element-wise
Grid3 Grid3::operator+(const Grid3& other) {
    if (nx != other.nx || ny != other.ny || nz != other.nz) {
        throw std::invalid_argument("Grid dimensions must match for addition");
    }

    Grid3 result(nx, ny, nz);
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
std::ostream& operator<<(std::ostream& os, const Grid3& grid) {
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
