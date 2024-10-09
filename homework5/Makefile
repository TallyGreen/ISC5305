# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Targets
TARGETS = main test

# Default target: build all executables
all: $(TARGETS)

# main.cpp compilation
main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

# test.cpp compilation
test: test.cpp
	$(CXX) $(CXXFLAGS) test.cpp -o test

# Clean up object files and executables
clean:
	-@rm -f main test 2>/dev/null || del main.exe test.exe
