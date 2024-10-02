#ifndef FUNCTION_H
#define FUNCTION_H

#include <cmath>
#include <iostream>
#include <string>

template <typename T>
class Function
{
public:
    std::string name;

    Function(std::string name_) : name(name_) {}
    virtual ~Function() {}
    
    // Evaluate the function at a point x
    virtual T operator()(T x) = 0;
    
    // Derivative for Newton's method
    virtual T fp(T x) = 0;
    
    // Verify the solution: takes the computed solution and checks the error
    virtual T verify(T computed_sol) {
        return std::fabs((*this)(computed_sol)); // The absolute error of f(computed_sol)
    }
};

// Function a: f(x) = sin(3x - 2)
template <typename T>
class SinFunction : public Function<T>
{
public:
    SinFunction() : Function<T>("sin(3x - 2)") {}

    T operator()(T x) override {
        return std::sin(3 * x - 2);
    }

    T fp(T x) override {
        return 3 * std::cos(3 * x - 2);
    }
};

// Function b: f(x) = x^3 - 6x^2 + 11x - 8
template <typename T>
class CubicFunction : public Function<T>
{
public:
    CubicFunction() : Function<T>("x^3 - 6x^2 + 11x - 8") {}

    T operator()(T x) override {
        return x * x * x - 6 * x * x + 11 * x - 8;
    }

    T fp(T x) override {
        return 3 * x * x - 12 * x + 11;
    }
};

// Function c: f(x) = log(x) + x^2 - 3
template <typename T>
class LogQuadraticFunction : public Function<T>
{
public:
    LogQuadraticFunction() : Function<T>("log(x) + x^2 - 3") {}

    T operator()(T x) override {
        return std::log(x) + x * x - 3;
    }

    T fp(T x) override {
        return 1 / x + 2 * x;
    }
};

#endif
