CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

all: homework2_3.x tests2.x

homework2_3.x: homework2_3.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

tests2.x: tests2.cpp homework2_3.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f homework2_3.x tests2.x

.PHONY: all clean