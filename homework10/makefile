# Makefile for Numerical Integration Project

CC = g++
CFLAGS = -Wall -O2 -pthread

# Targets for each part of the project
PART1 = part1
PART2 = part2
PART4 = part4

# Source files for each part
PART1_SRC = part1.cpp
PART2_SRC = part2.cpp
PART4_SRC = part4.cpp

# Object files for each part
PART1_OBJ = $(PART1).o
PART2_OBJ = $(PART2).o
PART4_OBJ = $(PART4).o

# Executables for each part
PART1_EXEC = $(PART1)_exec
PART2_EXEC = $(PART2)_exec
PART4_EXEC = $(PART4)_exec

all: $(PART1_EXEC) $(PART2_EXEC) $(PART4_EXEC)

$(PART1_EXEC): $(PART1_OBJ)
	$(CC) $(CFLAGS) -o $@ $<

$(PART2_EXEC): $(PART2_OBJ)
	$(CC) $(CFLAGS) -o $@ $<

$(PART4_EXEC): $(PART4_OBJ)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(PART1_EXEC) $(PART2_EXEC) $(PART4_EXEC)

.PHONY: all clean
