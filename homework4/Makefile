# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Targets
TARGETS = main main_plot main_no_delete main_float

# Build all executables
all: $(TARGETS)

# main.cpp compilation
main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

# main_plot.cpp compilation
main_plot: main_plot.cpp
	$(CXX) $(CXXFLAGS) main_plot.cpp -o main_plot

# main_no_delete.cpp compilation
main_no_delete: main_no_delete.cpp
	$(CXX) $(CXXFLAGS) main_no_delete.cpp -o main_no_delete

# main_float.cpp compilation
main_float: main_float.cpp
	$(CXX) $(CXXFLAGS) main_float.cpp -o main_float

# Clean up object files and executables
clean:
	-@rm -f main main_plot main_no_delete main_float 2>/dev/null || del main.exe main_plot.exe main_no_delete.exe main_float.exe
