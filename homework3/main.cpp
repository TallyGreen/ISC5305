#include "grid3d_1d_array.h"
#include "grid3d_vector.h"
#include "grid3d_new.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <numeric>
#include <stdexcept>  // To catch exceptions

using namespace std;
using namespace std::chrono;

// Function to time the summation of grids (Grid1, Grid2, Grid3)
void time_grid_summation(int n, std::ofstream& file, const std::string& grid_type) {
    vector<double> times;

    for (int i = 0; i < 5; i++) {
        auto start = high_resolution_clock::now();

        if (grid_type == "Grid1") {
            Grid1 grid(n, n, n);
            Grid1 grid_sum = grid + grid;
        } else if (grid_type == "Grid2") {
            Grid2 grid(n, n, n);
            Grid2 grid_sum = grid + grid;
        } else if (grid_type == "Grid3") {
            Grid3 grid(n, n, n);
            Grid3 grid_sum = grid + grid;
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();
        times.push_back(duration);
    }

    // Ignore the first timing and compute the average of the remaining 4
    double avg_time = accumulate(times.begin() + 1, times.end(), 0.0) / 4.0;

    file << n << "," << avg_time << "," << grid_type << "\n";
}

// Function to check the grid1 (1D array)
void check_grid_1d_array(int nx, int ny, int nz) {
    try {
        Grid1 grid(nx, ny, nz);
        cout << "Grid1 size: " << grid.getSize() << endl;
        cout << "Grid1 memory: " << grid.getMemory() << " bytes" << endl;

        for (auto i = 0; i < nx; i++) {
            for (auto j = 0; j < ny; j++) {
                for (auto k = 0; k < nz; k++) {
                    grid.set(i, j, k, 100 * i + 10 * j + k);
                }
            }
        }

        cout << "Grid1: " << grid;

        Grid1 grid_sum = grid + grid;
    } catch (const exception& e) {
        cerr << "Error in check_grid_1d_array: " << e.what() << endl;
    }
}

// Function to check the grid2 (vector-based)
void check_grid_vector(int nx, int ny, int nz) {
    try {
        Grid2 grid(nx, ny, nz);
        cout << "Grid2 size: " << grid.getSize() << endl;
        cout << "Grid2 memory: " << grid.getMemory() << " bytes" << endl;

        for (auto i = 0; i < nx; i++) {
            for (auto j = 0; j < ny; j++) {
                for (auto k = 0; k < nz; k++) {
                    grid.set(i, j, k, 100 * i + 10 * j + k);
                }
            }
        }

        cout << "Grid2: " << grid;

        Grid2 grid_sum = grid + grid;
    } catch (const exception& e) {
        cerr << "Error in check_grid_vector: " << e.what() << endl;
    }
}

// Function to check the grid3 (new-based)
void check_grid_new(int nx, int ny, int nz) {
    try {
        Grid3 grid(nx, ny, nz);
        cout << "Grid3 size: " << grid.getSize() << endl;
        cout << "Grid3 memory: " << grid.getMemory() << " bytes" << endl;

        for (auto i = 0; i < nx; i++) {
            for (auto j = 0; j < ny; j++) {
                for (auto k = 0; k < nz; k++) {
                    grid.set(i, j, k, 100 * i + 10 * j + k);
                }
            }
        }

        cout << "Grid3: " << grid;

        Grid3 grid_sum = grid + grid;
    } catch (const exception& e) {
        cerr << "Error in check_grid_new: " << e.what() << endl;
    }
}

int main() {
    // Perform checks on grids
    int nx = 2;
    int ny = 3;
    int nz = 4;
    check_grid_1d_array(nx, ny, nz);
    check_grid_vector(nx, ny, nz);
    check_grid_new(nx, ny, nz);

    // Timing for grid summation
    ofstream file("grid_timing.csv");
    file << "n,avg_time,grid_type\n";

    vector<int> sizes = {10, 50, 100, 200};

    // Measure and save timing results for different grid sizes and types
    for (auto n : sizes) {
        time_grid_summation(n, file, "Grid1");
        time_grid_summation(n, file, "Grid2");
        time_grid_summation(n, file, "Grid3");
    }

    file.close();
    cout << "Timing results saved to grid_timing.csv\n";
    return 0;
}
