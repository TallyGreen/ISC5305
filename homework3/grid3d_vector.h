/*
1) Create a 3D grid in 3 different ways: 

The object is a class: Grid
Size in each direction: nx, ny, nz

Method 1) 
*/
#ifndef __GRID3D_VECTOR_H__
#define __GRID3D_VECTOR_H__

#include <iostream>
#include <vector>

class Grid2
{
public:
    // Constructor
    Grid2(int nx_=1, int ny_=1, int nz_=1);
    // Destructor
    ~Grid2();
    // Get total size
    int getSize() const;
    // Get memory usage
    int getMemory() const;
    // Access an element (operator())
    double operator()(int i, int j, int k) const;
    // Set the value of an element
    void set(int i, int j, int k, double value);
    // Overload + operator
    Grid2 operator+(const Grid2& grid);
    // Overload << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Grid2& grid);

private:
    std::vector<std::vector<std::vector<double> > > data;
    int nx, ny, nz;
};

#endif
