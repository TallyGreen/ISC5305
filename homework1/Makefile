CC = g++
CCFLAGS = -std=c++11

# Specify the full path to your source file
SOURCES = D:/C++study/create_txt_fixed_csv.cpp
# Generate the corresponding object and executable file names
OBJECTS = $(SOURCES:.cpp=.o)
EXEC = $(SOURCES:.cpp=.x)
# The default target: build the executable
all: $(EXEC)

# Rule for compiling and linking
%.x: %.cpp
	$(CC) $(CCFLAGS) -o $@ $<

# Clean up rule to remove object and executable files
clean:
	rm -f $(OBJECTS) $(EXEC) *.o *.x
