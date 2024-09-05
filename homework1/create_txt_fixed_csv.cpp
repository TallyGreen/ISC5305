#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc != 5) {  // Should expect 4 arguments + program name
        std::cerr << "Usage: " << argv[0] << " min_value max_value n_time_steps output_file\n";
        return 1;
    }

    // Parse command-line arguments with error checking
    double min_value, max_value;
    int N;
    try {
        min_value = std::stod(argv[1]); // Use stod for better error handling
        max_value = std::stod(argv[2]);
        N = std::stoi(argv[3]);         // Use stoi for integer parsing
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid argument. Please enter valid numbers for min_value, max_value, and n_time_steps.\n";
        return 1;
    }

    std::string output_file = argv[4];

    // Check if N is valid
    if (N <= 1) {
        std::cerr << "Error: n_time_steps must be greater than 1.\n";
        return 1;
    }

    // Open the output file
    std::ofstream outfile(output_file);
    if (!outfile) {
        std::cerr << "Error: Could not open output file.\n";
        return 1;
    }

    // Write the CSV header
    outfile << "x,temperature\n";

    // Compute step size (h)
    double h = (max_value - min_value) / (N - 1);

    // Create the grid and compute temperatures
    std::vector<double> x(N), T(N);
    for (int i = 0; i < N; ++i) {
        x[i] = min_value + i * h;        // Calculate grid point
        T[i] = 1 - x[i] * x[i];          // Example temperature calculation
        outfile << x[i] << "," << T[i] << "\n";  // Write as CSV format
    }

    outfile.close();
    if (!outfile) {
        std::cerr << "Error: Failed to write to output file.\n";
        return 1;
    }

    std::cout << "Temperature distribution written to " << output_file << " as CSV file.\n";
    return 0;
}
