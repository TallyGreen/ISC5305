#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <vector>
#include "homework2_3.cpp"  // Assume this is your particle and vector class header

using namespace std;

// Tolerance level for floating-point comparison
const double EPSILON = 1e-5;

// Test Vector addition
void test_vector_addition() {
    Vector v1(1.0, 2.0);
    Vector v2(3.0, 4.0);
    Vector result = v1 + v2;
    assert(fabs(result[0] - 4.0) < EPSILON);
    assert(fabs(result[1] - 6.0) < EPSILON);
    cout << "test_vector_addition passed!" << endl;
}

// Test Vector scalar multiplication
void test_vector_scalar_multiplication() {
    Vector v1(1.0, 2.0);
    Vector result = v1 * 2.0;
    assert(fabs(result[0] - 2.0) < EPSILON);
    assert(fabs(result[1] - 4.0) < EPSILON);
    cout << "test_vector_scalar_multiplication passed!" << endl;
}

// Test dot product
void test_vector_dot_product() {
    Vector v1(1.0, 2.0);
    Vector v2(3.0, 4.0);
    double result = v1 * v2;
    assert(fabs(result - 11.0) < EPSILON);
    cout << "test_vector_dot_product passed!" << endl;
}

// Test Vector size
void test_vector_size() {
    Vector v1(1.0, 2.0);
    assert(v1.size() == 2);
    cout << "test_vector_size passed!" << endl;
}

// Test access to Vector elements
void test_vector_access() {
    Vector v1(1.0, 2.0);
    assert(fabs(v1[0] - 1.0) < EPSILON);
    assert(fabs(v1[1] - 2.0) < EPSILON);
    cout << "test_vector_access passed!" << endl;
}

// Test particle motion in 2D
void test_particle_2D_motion() {
    Particle particle(1.0, Vector(0.0, 0.0), Vector(1.0, 1.0));

    // Simulate for 1 second with a time step of 0.1s
    double dt = 0.1;
    for (double t = 0; t < 1.0; t += dt) {
        particle.update(t, dt, false);
    }

    // Expected approximate position after 1 second
    Vector expected_position = Vector(0.909297, -0.416147); // Corrected expected values for sin(2) and cos(2)

    // Get actual values
    double actual_x = particle.getPositionComponent(0);
    double actual_y = particle.getPositionComponent(1);

    // Print actual and expected values
    cout << "Actual X: " << actual_x << " Expected X: " << expected_position[0] << endl;
    cout << "Actual Y: " << actual_y << " Expected Y: " << expected_position[1] << endl;

    // Assertions
    assert(fabs(actual_x - expected_position[0]) < EPSILON);
    assert(fabs(actual_y - expected_position[1]) < EPSILON);

    cout << "test_particle_2D_motion passed!" << endl;
}



// Test particle motion in 3D
void test_particle_3D_motion() {
    Particle particle(1.0, Vector(0.0, 0.0, 0.0), Vector(1.0, 1.0, 1.0));

    // Simulate for 1 second with a time step of 0.1s
    double dt = 0.1;
    for (double t = 0; t < 1.0; t += dt) {
        particle.update(t, dt, true);
    }

    // Expected approximate position after 1 second of motion with oscillatory force
    Vector expected_position = Vector(0.479425, 0.841471, 0.070737); // Approx. using sin(2*1), cos(2*1), cos(1.5*1)
    assert(fabs(particle.getPositionComponent(0) - expected_position[0]) < EPSILON);
    assert(fabs(particle.getPositionComponent(1) - expected_position[1]) < EPSILON);
    assert(fabs(particle.getPositionComponent(2) - expected_position[2]) < EPSILON);
    cout << "test_particle_3D_motion passed!" << endl;
}

// Main test runner
int main() {
    // Run Vector tests
    test_vector_addition();
    test_vector_scalar_multiplication();
    test_vector_dot_product();
    test_vector_size();
    test_vector_access();

    // Run Particle tests
    test_particle_2D_motion();
    test_particle_3D_motion();

    cout << "All tests passed!" << endl;
    return 0;
}