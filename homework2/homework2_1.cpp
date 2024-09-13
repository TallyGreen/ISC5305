#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
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
    Vector(double x, double y) : components_{x, y} {
    } 
    // Fill and document this function <<<<<<
    Vector(double x, double y, double z) : components_{x, y, z} {}

    // Fill and document this destructor  <<<<<
    ~Vector() {};

    // Fill and document this function which returns the number of 
    // components of the `Vector`   <<<<
    int size() const {
        return components_.size();
    }

    // Fill and document this function, which should work for any size vector  <<<<
    Vector operator+(const Vector &other) const {
        vector<double> result;
        for (int i = 0; i < size(); ++i) {
            result.push_back(components_[i] + other.components_[i]);
        }
        return Vector(result);
    }

    // I overloaded the [] operator
    // Add an error check in case 'i' goes out of bounds <<<<
    double operator[](const int i) const {
        if (i < 0 || i >= size()) {
            throw out_of_range("Index out of bounds.");
        }
        return components_[i];
    }

    // Fill and document this function <<<<<
    // Product with a scalar  (vector * scalar)
    //Overload operator* for scalar multiplication (vector * scalar)

    Vector operator*(const double &scalar) const {
        vector<double> result;
        for (auto &comp : components_) {
            result.push_back(comp * scalar);
        }
        return Vector(result);
    }
    // Fill and document this function which should work for any size vector <<<<<
    // Overload operator* for scalar * vector (friend function)
    friend Vector operator*(const double scalar, const Vector &v) {
        return v * scalar; // Leverage the previous operator
    }

    // Fill and document this function <<<<<
    // Dot product: Vector * Vector
    double operator*(const Vector &other) const {
        double dotProduct = 0;
        for (int i = 0; i < size(); ++i) {
            dotProduct += components_[i] * other.components_[i];
        }
        return dotProduct;
    }


    friend ostream &operator<<(ostream &os, const Vector &v)
    {
        os << "(";
        for (int i = 0; i < v.size(); ++i)
        {
            os << v.components_[i];
            if (i < v.size() - 1)
                os << ", ";
        }
        os << ")";
        return os;
    }
    
    double norm(const string &type) const
    {
        if (type == "L1") {
            double sum = 0.0;
            for (int i = 0; i < size(); ++i) {
                sum += abs(components_[i]); // Summing the absolute values of the components
            }
            return sum;
        } 
        else if (type == "L2") {
            double sumSquares = 0.0;
            for (int i = 0; i < size(); ++i) {
                sumSquares += components_[i] * components_[i]; // Summing the squares of the components
            }
            return sqrt(sumSquares); // Taking the square root of the sum
        } 
        else if (type == "Linf") {
            double maxVal = 0.0;
            for (int i = 0; i < size(); ++i) {
                maxVal = max(maxVal, abs(components_[i])); // Finding the maximum absolute value
            }
            return maxVal;
        } 
        else {
            throw invalid_argument("Unsupported norm type. Choose from 'L1', 'L2', or 'Linf'.");
        }
    }

};

// Fill and document this function. Note the pass by reference and the fact that the 
// force `f` is not `const`. The reference mean that `f` points to an 
// existing variable. `f` is used with a dot like a normal variable, but in 
// reality is an address. Therefore, changing `f` inside the function, changes
// it in the calling function.
Vector &force(Vector &f, double t)
{
    // Apply some scaling to the force based on time t (example: scaling by time)
    f = f * t;
    return f;
}

// Fill and document this function. Type is "L1", "L2", or "Linf"  <<<<<
// Calculate the norm of the vector based on the norm type (L1, L2, Linf)


// Particle class
class Particle
{
public:
    // Last two arguments are position and velocity at time zero
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
        if (velocity_.size() == 0)
        {
            throw runtime_error("printState: Vector is empty");
        }
        cout << "Particle - Mass: " << mass_ << ", Position: " << position_
             << ", Velocity: " << velocity_ << ", Speed: " << velocity_.norm("L2") << endl;
    }

    // Update particle properties at time t, using time step dt
    void update(double t, double dt)
    {
        // Apply Euler method: Update velocity and position based on force and time step
        Vector acceleration = force_ * (1.0 / mass_); // a = F/m
        velocity_ = velocity_ + acceleration * dt;    // v_new = v_old + a * dt
        position_ = position_ + velocity_ * dt;       // x_new = x_old + v_new * dt

        cout << "Updated particle at time " << t << ": " << endl;
        printState();
    }

    // Force function already provided
    Vector &force(Vector &f, double t)
    {
        return f;
    }

public:
    Vector getPosition() const {
        return position_;
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
}

void writeTrajectory2D(Particle &particle, const string &filename, double totalTime, double timeStep) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    double time = 0.0;
    while (time <= totalTime) {
        Vector pos = particle.getPosition();
        outFile << time << " " << pos[0] << " " << pos[1] << endl;
        particle.update(time, timeStep);
        time += timeStep;
    }

    outFile.close();
}

// Function to write the particle trajectory to file for 3D particles
void writeTrajectory3D(Particle &particle, const string &filename, double totalTime, double timeStep) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    double time = 0.0;
    while (time <= totalTime) {
        Vector pos = particle.getPosition();
        outFile << time << " " << pos[0] << " " << pos[1] << " " << pos[2] << endl;
        particle.update(time, timeStep);
        time += timeStep;
    }

    outFile.close();
}

// ----------------------------------------------------------------------
#ifdef RUN_HW
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
    double totalTime = 10.0;  // Total simulation time
    double timeStep = 0.1;    // Time step for updates
    // (seen homework assignment pdf file)


    // Output the 2D and 3D trajectories to two files whose names are read from the command line.  
    // "traject_3d.txt". Do not change the file names. 
    // "traject_2d.txt" should contain three columns: time, x, y
    // "traject_3d.txt" should contain four columns: time, x, y, z
    // Then read this file with a Python program and visualize the data. Create one plot for the 2D
    // trajectory, and another plot for the 3D trajectory. Add axis labels and title for each plot. 
    // Store the plot in images/ folder. 
    writeTrajectory2D(particle2D, "traject_2d.txt", totalTime, timeStep);
    writeTrajectory3D(particle3D, "traject_3d.txt", totalTime, timeStep);

    return 0;
}
#endif 
