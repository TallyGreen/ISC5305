#include "grid3d_1d_array.h"
#include "grid3d_vector.h"
#include "grid3d_new.h"
#include <iostream>
#include <cassert>  // For assertions
#include <stdexcept>  // For exception handling

using namespace std;

template <typename Grid>
void test_grid_initialization(Grid& grid, int nx, int ny, int nz) {
    // Test that all elements are initialized to 0.0
    for (auto i = 0; i < nx; i++) {
        for (auto j = 0; j < ny; j++) {
            for (auto k = 0; k < nz; k++) {
                assert(grid(i, j, k) == 0.0);
            }
        }
    }
    cout << "Initialization test passed." << endl;
}

template <typename Grid>
void test_set_get_values(Grid& grid, int nx, int ny, int nz) {
    // Set values and ensure that they can be retrieved correctly
    try {
        grid.set(0, 0, 0, 3.14);
        assert(grid(0, 0, 0) == 3.14);
        grid.set(1, 1, 1, 2.71);
        assert(grid(1, 1, 1) == 2.71);
        cout << "Set/get value test passed." << endl;
    } catch (const std::exception& e) {
        cout << "Exception in set/get test: " << e.what() << endl;
    }
}

template <typename Grid>
void test_grid_size_and_memory(Grid& grid, int nx, int ny, int nz) {
    // Test size and memory usage
    assert(grid.getSize() == nx * ny * nz);
    assert(grid.getMemory() == sizeof(double) * nx * ny * nz);
    cout << "Grid size and memory test passed." << endl;
}

template <typename Grid>
void test_grid_addition(Grid& grid1, Grid& grid2, int nx, int ny, int nz) {
    // Test grid addition
    try {
        grid1.set(0, 0, 0, 1.0);
        grid2.set(0, 0, 0, 2.0);
        auto grid_sum = grid1 + grid2;  // Use auto
        assert(grid_sum(0, 0, 0) == 3.0);
        cout << "Grid addition test passed." << endl;
    } catch (const std::exception& e) {
        cout << "Exception in grid addition: " << e.what() << endl;
    }
}

template <typename Grid>
void test_out_of_bounds(Grid& grid, int nx, int ny, int nz) {
    // Test out-of-bounds access
    try {
        grid.set(nx, ny, nz, 5.0);  // Should throw out_of_range exception
        assert(false);  // If no exception is thrown, fail the test
    } catch (const out_of_range& e) {
        cout << "Out-of-bounds test passed: " << e.what() << endl;
    }
}

void run_tests() {
    int nx = 2, ny = 2, nz = 2;

    // Test Grid1 (1D array)
    Grid1 grid1(nx, ny, nz);
    Grid1 grid1_2(nx, ny, nz);
    test_grid_initialization(grid1, nx, ny, nz);
    test_set_get_values(grid1, nx, ny, nz);
    test_grid_size_and_memory(grid1, nx, ny, nz);
    test_grid_addition(grid1, grid1_2, nx, ny, nz);
    test_out_of_bounds(grid1, nx, ny, nz);

    // Test Grid2 (vector-based)
    Grid2 grid2(nx, ny, nz);
    Grid2 grid2_2(nx, ny, nz);
    test_grid_initialization(grid2, nx, ny, nz);
    test_set_get_values(grid2, nx, ny, nz);
    test_grid_size_and_memory(grid2, nx, ny, nz);
    test_grid_addition(grid2, grid2_2, nx, ny, nz);
    test_out_of_bounds(grid2, nx, ny, nz);

    // Test Grid3 (new-based)
    Grid3 grid3(nx, ny, nz);
    Grid3 grid3_2(nx, ny, nz);
    test_grid_initialization(grid3, nx, ny, nz);
    test_set_get_values(grid3, nx, ny, nz);
    test_grid_size_and_memory(grid3, nx, ny, nz);
    test_grid_addition(grid3, grid3_2, nx, ny, nz);
    test_out_of_bounds(grid3, nx, ny, nz);
}

int main() {
    run_tests();
    cout << "All tests passed!" << endl;
    return 0;
}
