# Homework 1
## Question
Task: Create a command-line tool that accepts input parameters (e.g., grid size $N$, initial temperature) for a simple 1D heat distribution simulation on a uniform grid and outputs the initial grid configuration $(x, T)$ to an output file. The input and output files must also be read from the separate command line. As in the previous question, create a separate program to generate the 1D heat distribution. Use Python to plot the initial temperature profile: write the 1D heat distribution to a file and read this file using Python. For the 1D heat distribution, use $T = 1. - x^2$, and the grid is defined by $x ∈ [a, b]$, where $a$ and $b$ are read from the command line, as well as the number of points $N$. It is understood that the homework statement is slightly vague. That means that we can more easily detect if you are copying from each other, which results in a score of zero.
Tool Assistance: Use AI to generate boilerplate code for parsing command-line arguments and error handling. Ask the AI for the kind of error handling that would be useful once the code without error handling is created.

First time code:
```cpp
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
```
Error handling for argument parsing with `std::stod` and `std::stoi` for better robustness.
Validation for `n_time_steps` to avoid potential issues with small values.
Better file handling by checking the success of the file writing operation.

Seconde time
```cpp
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

    // Compute step size (h)
    double h = (max_value - min_value) / (N - 1);

    // Create the grid and compute temperatures
    std::vector<double> x(N), T(N);
    for (int i = 0; i < N; ++i) {
        x[i] = min_value + i * h;        // Calculate grid point
        T[i] = 1 - x[i] * x[i];          // Example temperature calculation
        outfile << x[i] << " " << T[i] << "\n";  // Write to file
    }

    outfile.close();
    if (!outfile) {
        std::cerr << "Error: Failed to write to output file.\n";
        return 1;
    }

    std::cout << "Temperature distribution written to " << output_file << "\n";
    return 0;
}
```

Error can't export csv.file

Third time:
```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc != 5) {  // argv[]: An array of C-style strings representing the actual command-line arguments
        std::cerr << "Usage: " << argv[0] << " min_value max_value n_time_steps output_file\n";
        return 1;
    }

    // Parse command-line arguments with error checking
    double min_value, max_value;
    int N;
    try {
        min_value = std::stod(argv[1]); //he part of the main() function that parses the command-line arguments checks if the correct number of arguments is provided and then converts them to the appropriate types
        max_value = std::stod(argv[2]);
        N = std::stoi(argv[3]);         
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

This is the data produced by function:
x,temperature
-1,0
-0.979798,0.0399959
-0.959596,0.0791756
-0.939394,0.117539
-0.919192,0.155086
-0.89899,0.191817
-0.878788,0.227732
-0.858586,0.26283
-0.838384,0.297113
-0.818182,0.330579
-0.79798,0.363228
-0.777778,0.395062
-0.757576,0.426079
-0.737374,0.45628
-0.717172,0.485665
-0.69697,0.514233
-0.676768,0.541986
-0.656566,0.568922
-0.636364,0.595041
-0.616162,0.620345
-0.59596,0.644832
-0.575758,0.668503
-0.555556,0.691358
-0.535354,0.713397
-0.515152,0.734619
-0.494949,0.755025
-0.474747,0.774615
-0.454545,0.793388
-0.434343,0.811346
-0.414141,0.828487
-0.393939,0.844812
-0.373737,0.86032
-0.353535,0.875013
-0.333333,0.888889
-0.313131,0.901949
-0.292929,0.914192
-0.272727,0.92562
-0.252525,0.936231
-0.232323,0.946026
-0.212121,0.955005
-0.191919,0.963167
-0.171717,0.970513
-0.151515,0.977043
-0.131313,0.982757
-0.111111,0.987654
-0.0909091,0.991736
-0.0707071,0.995001
-0.0505051,0.997449
-0.030303,0.999082
-0.010101,0.999898
0.010101,0.999898
0.030303,0.999082
0.0505051,0.997449
......