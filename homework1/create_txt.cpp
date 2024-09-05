#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] << " min_value max_value n_time_steps output_file\n";
        return 1;
    }

    // Parse command-line arguments
    double min_value = std::atof(argv[1]); // Convert to float
    double max_value = std::atof(argv[2]);
    int N = std::atoi(argv[3]);    // Convert to integer
    std::string output_file = argv[4];

    // Open the output file
    std::ofstream outfile(output_file);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open output file.\n";
        return 1;
    }

    // Compute step size (h)
    double h = (max_value - min_value) / (N - 1);

    // Create the grid and compute temperatures
    std::vector<double> x(N), T(N);
    for (int i = 0; i < N; ++i) {
        x[i] = min_value + i * h;         // Calculate grid point
        T[i] = 1 - x[i] * x[i];   // Calculate temperature
        outfile << x[i] << " " << T[i] << "\n";  // Write to file
    }

    outfile.close();
    std::cout << "Temperature distribution written to " << output_file << "\n";
    return 0;
}
