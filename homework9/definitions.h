#ifndef __DEFINITIONS__H__
#define __DEFINITIONS__H__

#include <functional>
#include <unordered_map>
#include <cmath>
#include <iostream>

// Define a type alias for mathematical functions
using MathFunction = std::function<double(double)>;

// Base Function class
class Function {
protected:
    mutable unsigned int count{0};  // Tracks number of evaluations
    bool uses_cache{false};         // Indicates if caching is enabled

public:
    virtual double operator()(double x) const = 0;  // Pure virtual function
    virtual ~Function() = default;

    // Returns the evaluation count
    unsigned int getCount() const { return count; }

    // Resets the evaluation count
    void resetCounter() const { count = 0; }

    // Clears the cache, if any (placeholder in base class)
    virtual void clearCache() const {}

    // Returns whether caching is enabled
    bool isCacheEnabled() const { return uses_cache; }

    // Evaluates the function and increments count
    double evaluate(double x) const {
        count++;  // Increment count for each evaluation
        return operator()(x);
    }
};

// CachedFunction class to cache results of function evaluations
class CachedFunction : public Function {
private:
    MathFunction func_;
    mutable std::unordered_map<int, double> cache_; 
    mutable int evaluationCount;  
    double tol;  

public:
    explicit CachedFunction(MathFunction func, double tolerance = 1e-7)
        : func_(func), evaluationCount(0),tol(tolerance){}

    
    double operator()(double x) const override {
        int bin = static_cast<int>(std::round(x / tol));
        auto it = cache_.find(bin);  
        if (it != cache_.end()) {
            std::cout << "Cache hit for x = " << x << ", returning cached result." << std::endl;
            return it->second; 
        }
        double result = func_(x); 
        cache_[bin] = result;  
        evaluationCount++;  
        std::cout << "Evaluating function at x = " << x << ", result = " << result << std::endl;
        std::cout << "Updated evaluation count: " << evaluationCount << std::endl;
        return result;
    }


    void resetEvaluations() { evaluationCount = 0; }
    void clearCache() const { cache_.clear(); }
    int getEvaluationCount() const { return evaluationCount; }
};

// FastCachedFunction class with basic integer binning for fast lookups
class FastCachedFunction : public Function {
private:
    MathFunction func_;  // Underlying mathematical function
    mutable std::unordered_map<int, double> cache_;  // Cache with integer bins
    double tol_;  // Tolerance for binning

    // Converts x to an integer bin index based on tolerance
    int getBin(double x) const {
        return static_cast<int>(std::round(x / tol_));
    }

public:
    // Constructor accepts a MathFunction and tolerance
    FastCachedFunction(MathFunction func, double tol = 1e-7) : func_(func), tol_(tol) {
        uses_cache = true;
    }

    // Override operator() to include caching with bins
    double operator()(double x) const override {
        int bin = getBin(x);
        auto it = cache_.find(bin);
        if (it != cache_.end()) {
            return it->second;  // Return cached result if it exists
        }
        double result = func_(x);  // Otherwise, evaluate and cache result
        cache_[bin] = result;
        count++;
        return result;
    }

    // Clears the cache
    void clearCache() const override { cache_.clear(); }
};

#endif // __DEFINITIONS__H__
