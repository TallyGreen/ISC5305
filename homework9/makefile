CXX = g++
CXXFLAGS = -std=c++11

SRC = main.cpp integration_methods.cpp
TARGET = main

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
