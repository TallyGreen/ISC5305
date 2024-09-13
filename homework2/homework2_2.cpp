 #include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

// Vector class to represent both 2D and 3D vectors
class Vector
{
public:
    vector<double> components_;

public:
    Vector(vector<double> components) : components_(components) {}

    Vector(double x, double y) : components_{x, y} {}  // 2D constructor

    Vector(double x, double y, double z) : components_{x, y, z} {}  // 3D constructor

    ~Vector() {}

    // Return the number of components of the Vector
    int size() const {
        return components_.size();
    }

    // Vector addition
    Vector operator+(const Vector &other) const
    {
        if (size() != other.size()) throw runtime_error("Vector sizes must match!");
        vector<double> result(size());
        for (size_t i = 0; i < size(); i++) {
            result[i] = components_[i] + other.components_[i];
        }
        return Vector(result);
    }

    // Element access with bounds check
    double operator[](const int i) const
    {
        if (i < 0 || i >= size()) throw out_of_range("Index out of bounds");
        return components_[i];
    }

    // Scalar multiplication
    Vector operator*(const double &scalar) const
    {
        vector<double> result(size());
        for (size_t i = 0; i < size(); i++) {
            result[i] = components_[i] * scalar;
        }
        return Vector(result);
    }

    // Scalar * vector
    friend Vector operator*(const double scalar, const Vector &v)
    {
        return v * scalar;
    }

    // Dot product: Vector * Vector
    double operator*(const Vector &other) const
    {
        if (size() != other.size()) throw runtime_error("Vector sizes must match!");
        double dot_product = 0;
        for (size_t i = 0; i < size(); i++) {
            dot_product += components_[i] * other.components_[i];
        }
        return dot_product;
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

// Force function for 2D
Vector force2D(double t)
{
    return Vector(sin(2 * t), cos(2 * t));
}


// Force function for 3D
Vector force3D(double t)
{
    return Vector(sin(2 * t), cos(2 * t), cos(1.5 * t));
}

// Compute vector norms
double norm(const Vector &v, const string type)
{
    double result = 0.0;
    if (type == "L1") {
        for (double c : v.components_) result += abs(c);
    } else if (type == "L2") {
        for (double c : v.components_) result += c * c;
        result = sqrt(result);
    } else if (type == "Linf") {
        for (double c : v.components_) result = max(result, abs(c));
    } else {
        throw invalid_argument("Unknown norm type");
    }
    return result;
}

class Particle
{
public:
    Particle(double mass, const Vector &position, const Vector &velocity)
        : mass_(mass), position_(position), velocity_(velocity)
    {
        cout << "Particle created at position " << position_ << endl;
    }

    ~Particle()
    {
        cout << "Particle destroyed at position " << position_ << endl;
    }

    void update(double t, double dt, bool is3D)
    {
        // Recalculate the force at time t
        Vector current_force = is3D ? force3D(t) : force2D(t);

        // Update velocity using the current force
        velocity_ = velocity_ + current_force * dt;

        // Update position using the updated velocity
        position_ = position_ + velocity_ * dt;
    }

    void printState() const
    {
        if (velocity_.size() == 0) throw runtime_error("printState: Vector is empty");
        cout << "Particle - Mass: " << mass_ << ", Position: " << position_
             << ", Velocity: " << velocity_ << ", Speed: " << norm(velocity_, "L2") << endl;
    }

    double getPositionComponent(int index) const {
        return position_[index];
    }

private:
    double mass_;
    Vector position_;
    Vector velocity_;
};



void simulateParticle(Particle &particle, bool is3D, double dt, double t_max, const string &filename)
{
    ofstream outfile(filename);
    for (double t = 0; t <= t_max; t += dt) {
        // Update the particle's state using the current time t and time step dt
        particle.update(t, dt, is3D);
        
        // Output particle's position to file (write x, y, and optionally z)
        outfile << t << " " << particle.getPositionComponent(0) << " " << particle.getPositionComponent(1);
        if (is3D) {
            outfile << " " << particle.getPositionComponent(2);
        }
        outfile << endl;
    }
    outfile.close();
}




int main()
{
    try {
        cout << "Starting simulations..." << endl;

        // Create a 2D particle with mass 1
        Particle particle2D(1.0, Vector(0.0, 0.0), Vector(0.0, 0.0));  // 2D, initial velocity set to (0,0)

        // Create a 3D particle with mass 1
        Particle particle3D(1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0));  // 3D, initial velocity set to (0,0,0)

        // Simulate particles
        cout << "Simulating 2D particle..." << endl;
        simulateParticle(particle2D, false, 0.02, 4.0, "traject_2d.txt");
        cout << "2D simulation completed. Results written to traject_2d.txt" << endl;

        cout << "Simulating 3D particle..." << endl;
        simulateParticle(particle3D, true, 0.02, 4.0, "traject_3d.txt");
        cout << "3D simulation completed. Results written to traject_3d.txt" << endl;

        cout << "All simulations completed successfully." << endl;
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
