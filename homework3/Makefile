# Compiler
CXX = g++
CXXFLAGS = -Wall -g -std=c++17

# Executable names
TEST_EXEC = test_grid
MAIN_EXEC = main_grid

# Source files for both executables
SRCS_TEST = test_grid.cpp grid3d_1d_array.cpp grid3d_vector.cpp grid3d_new.cpp
SRCS_MAIN = main.cpp grid3d_1d_array.cpp grid3d_vector.cpp grid3d_new.cpp

# Object files for both executables
OBJS_TEST = $(SRCS_TEST:.cpp=.o)
OBJS_MAIN = $(SRCS_MAIN:.cpp=.o)

# Target to build both executables
all: $(TEST_EXEC) $(MAIN_EXEC)

# Rule to link object files to create the test executable
$(TEST_EXEC): $(OBJS_TEST)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(OBJS_TEST)

# Rule to link object files to create the main executable
$(MAIN_EXEC): $(OBJS_MAIN)
	$(CXX) $(CXXFLAGS) -o $(MAIN_EXEC) $(OBJS_MAIN)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up by removing the object files and both executables
ifeq ($(OS),Windows_NT)
clean:
	del /f *.o $(TEST_EXEC).exe $(MAIN_EXEC).exe
else
clean:
	rm -f $(OBJS_TEST) $(OBJS_MAIN) $(TEST_EXEC) $(MAIN_EXEC)
endif

# Run the test executable
run_test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Run the main executable
run_main: $(MAIN_EXEC)
	./$(MAIN_EXEC)
