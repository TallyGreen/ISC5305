#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Learn about any concept you don't know or understand with AI. 
// Use the `auto` keyword a much as you can. 
// Use range-based loops as much as you can. 

// Vector class to represent both 2D and 3D vectors
class Vector
{
private:
    vector<double> components_;

public:
    Vector(vector<double> components) : components_(components) {}

    // Fill and document this function <<<<<
    Vector(double x, double y) {
    };  

    // Fill and document this function <<<<<<
    Vector(double x, double y, double z) : components_{x, y, z} {}

    // Fill and document this destructor  <<<<<
    ~Vector() {};

    // Fill and document this function which returns the number of 
    // components of the `Vector`   <<<<
    int size() const {
        return 0;
    }

    // Fill and document this function, which should work for any size vector  <<<<
    Vector operator+(const Vector &other) const
    {
        return Vector(0., 0.);
    }

    // I overloaded the [] operator
    // Add an error check in case 'i' goes out of bounds <<<<
    double operator[](const int i) const
    {
        return components_[i];
    }

    // Fill and document this function <<<<<
    // Product with a scalar  (vector * scalar)
    // scalar * vector won't work
    Vector operator*(const double &other) const
    {
        return Vector(0., 0.);
    }

    // Fill and document this function which should work for any size vector <<<<<
    // scalar * vector
    friend Vector operator*(const double scalar, const Vector &other)
    {
        return Vector(0., 0.);
    }

    // Fill and document this function <<<<<
    // Dot product: Vector * Vector
    double operator*(const Vector &other) const
    {
        return 0.;  // Replace by correct return value
    }

    friend ostream &operator<<(ostream &os, const Vector &v)
    {
        os << "(";
        for (size_t i = 0; i < v.size(); ++i)
        {
            os << v.components_[i];
            if (i < v.size() - 1)
                os << ", ";
        }
        os << ")";
        return os;
    }
};

// Fill and document this function. Note the pass by reference and the fact that the 
// force `f` is not `const`. The reference mean that `f` points to an 
// existing variable. `f` is used with a dot like a normal variable, but in 
// reality is an address. Therefore, changing `f` inside the function, changes
// it in the calling function.
Vector &force(Vector &f, double t)
{
    return f;
}

// Fill and document this function. Type is "L1", "L2", or "Linf"  <<<<<
double norm(const Vector &v, const string type)
{
    return 0.;
}

class Particle
{
public:
    // Last two argument are position and velocity at time zero
    Particle(double mass, const Vector &position, const Vector &velocity, const Vector &force)
        : mass_(mass), position_(position), velocity_(velocity), force_(force)
    {
        cout << "Particle created at position " << position_ << endl;
    }

    ~Particle()
    {
        cout << "Particle destroyed at position " << position_ << endl;
    }

    void updatePosition(double time)
    {
        position_ = position_ + velocity_ * time;
    }

    void printState() const
    {
        if (velocity_.size() == 0) {
            throw runtime_error("printState: Vector is empty");
        }
        cout << "Particle - Mass: " << mass_ << ", Position: " << position_
             << ", Velocity: " << velocity_ << ", Speed: " << norm(velocity_, "L2") << endl;
    }

    // Fill this function  <<<<<<
    // Update particle properties at time t, using time step dt.
    // force_: force applied to the particle
    void update(double t, double dt)
    {
    }

    // Fill and document this function
    Vector &force(Vector &f, double t)
    {
        return f;
    }

private:
    double mass_;
    Vector position_;
    Vector velocity_;
    Vector force_;
};

// Leave this function unchanged, but call it from main <<<<<
void test_operators()
{
    cout << "Inside test operators" << endl;

    Vector v1(1.0, 2.0);
    Vector v2(3.0, 4.0);
    cout << "v2: " << v2 << endl;
    cout << "v1: " << v1 << endl;
    cout << "3.2 * v1: " << 3.2 * v1 << endl;
    cout << "v1 * 3.2: " << v1 * 3.2 << endl;
    cout << "v1 + v2: " << v1 + v2 << endl;
    double prod;
    prod = (2. * v1 + 3. * v2) * (v1 + v2);
    cout << "( 2.*v1 + 3.*v2 ) * (v1 + v2) = " << prod << endl;
    prod = (2. * v1 + 3. * v2) * v1;
    cout << "( 2.*v1 + 3.*v2 ) * v1 = " << prod << endl;
    prod = v1 * v2;
    cout << "v1 * v2 : " << prod << endl;
    cout << "Vector addition: " << v1 << " + " << v2 << " = " << v1 + v2 << endl;

    // test particles
}

// ----------------------------------------------------------------------
int main()
{
    // Create a 2D particle with mass 1 and force (0., 0.)
    Particle particle2D(1.0, Vector(0.0, 0.0), Vector(1.0, 2.0), Vector(0., 0.));
    cout << "Initial state of 2D particle:" << endl;
    particle2D.printState();

    // Change function to take applied force into account
    particle2D.updatePosition(2.0);
    cout << "2D particle after 2 seconds:" << endl;
    particle2D.printState();

    // Create a 3D particle
    Particle particle3D(1.0, Vector(0.0, 0.0, 0.0), Vector(1.0, 2.0, 3.0), Vector(0., 0.));
    cout << "\nInitial state of 3D particle:" << endl;
    particle3D.printState();

    particle3D.updatePosition(2.0); 

    cout << "3D particle after 2 seconds:" << endl;
    particle3D.printState();

    // Demonstrate vector addition. The code below must execute properly
    test_operators();

    // Handle particles
    Vector f2d{0., 0.};     // regular parentheses
    Vector f3d{0., 0., 0.}; // curly brackets, safer. To be studied later.

    cout << "f2d: " << f2d << endl;
    cout << "f3d: " << f3d << endl;

    double t = 1.0;
    cout << force(f2d, t) << endl;
    cout << force(f3d, t) << endl;

    // Add code to record the movement of 2D and 3D particles based on Euler's formula
    // (seen homework assignment pdf file)


    // Output the 2D and 3D trajectories to two files whose names are read from the command line.  
    // "traject_3d.txt". Do not change the file names. 
    // "traject_2d.txt" should contain three columns: time, x, y
    // "traject_3d.txt" should contain four columns: time, x, y, z
    // Then read this file with a Python program and visualize the data. Create one plot for the 2D
    // trajectory, and another plot for the 3D trajectory. Add axis labels and title for each plot. 
    // Store the plot in images/ folder. 

    return 0;
}
