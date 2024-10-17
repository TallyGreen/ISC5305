#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <utility>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <complex>
#include <functional>

// Abstract base class for scientific objects
class ScientificObject {
public:
    virtual void compute() const = 0;
    virtual ~ScientificObject() = default;
};

// Derived class: Vector Calculation
class VectorCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing vector calculation..." << std::endl;
    }
};

// Derived class: Matrix Calculation
class MatrixCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing matrix calculation..." << std::endl;
    }
};

// New Derived Class: Tensor Calculation
class TensorCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing tensor calculation..." << std::endl;
    }
};

// Custom exception class for duplicate elements
class DuplicateElementException : public std::runtime_error {
public:
    explicit DuplicateElementException(const std::string& message)
        : std::runtime_error("Duplicate element: " + message) {}
};

// Template function to process arithmetic data
template <typename T>
void process_data(const T& data) {
    static_assert(std::is_arithmetic<T>::value, "Template type must be arithmetic.");
    std::cout << "Processing data: " << data << std::endl;
}

// Overloaded function for std::string
template <>
void process_data(const std::string& data) {
    if (data.empty()) {
        throw std::invalid_argument("String cannot be empty.");
    }
    std::cout << std::string(data.rbegin(), data.rend()) << std::endl; // Reverse string
}

// Specialized template function for std::complex<double>
template <>
void process_data(const std::complex<double>& c) {
    std::cout << "Processing complex number: Real = " << c.real()
              << ", Imaginary = " << c.imag() << std::endl;
}

// Template class for ScientificContainer
template <typename T>
class ScientificContainer {
private:
    std::list<std::pair<T, std::shared_ptr<ScientificObject>>> container;
    std::unordered_map<T, std::tuple<int, double, std::string>> metadata;
    std::unordered_set<T> unique_elements;
    std::function<void()> metadata_callback;

public:
    // Add element with duplicate check and custom exception
    void add_element(const T& key, std::shared_ptr<ScientificObject> obj) {
        if (unique_elements.find(key) != unique_elements.end()) {
            throw DuplicateElementException(std::to_string(key));
        }
        container.emplace_back(key, obj);
        unique_elements.insert(key);
    }

    // Add metadata with optional callback
    void add_metadata(const T& key, const std::tuple<int, double, std::string>& data,
                      std::function<void()> callback = nullptr) {
        if (metadata.find(key) != metadata.end()) {
            throw std::runtime_error("Metadata for this key already exists.");
        }
        metadata[key] = data;
        if (callback) {
            metadata_callback = callback;
        }
    }

    // Print metadata and execute callback if available
    void print_metadata() const {
        for (const auto& [key, data] : metadata) {
            std::cout << "Metadata for key " << key << ": ("
                      << std::get<0>(data) << ", "
                      << std::get<1>(data) << ", "
                      << std::get<2>(data) << ")" << std::endl;
        }
        if (metadata_callback) {
            metadata_callback();
        }
    }

    // Compute all elements
    void compute_all() const {
        for (const auto& [key, obj] : container) {
            try {
                std::cout << "Computing for key: " << key << std::endl;
                obj->compute();
            } catch (const std::exception& e) {
                std::cerr << "Error during computation for key " << key << ": " << e.what() << std::endl;
            }
        }
    }

    // Lambda-based filtering mechanism
    void filter_elements(std::function<bool(const T&)> condition) const {
        for (const auto& [key, _] : container) {
            if (condition(key)) {
                std::cout << "Key " << key << " satisfies the filter condition." << std::endl;
            }
        }
    }

    // Range-based iteration support
    auto begin() const { return container.begin(); }
    auto end() const { return container.end(); }
};

int main() {
    try {
        // Create a ScientificContainer instance
        ScientificContainer<int> sci_container;

        // Adding elements to the container
        sci_container.add_element(1, std::make_shared<VectorCalculation>());
        sci_container.add_element(2, std::make_shared<MatrixCalculation>());
        sci_container.add_element(3, std::make_shared<TensorCalculation>());

        // Adding metadata with a callback
        sci_container.add_metadata(1, std::make_tuple(42, 3.14, "Vector"), []() {
            std::cout << "Metadata accessed!" << std::endl;
        });
        sci_container.add_metadata(2, std::make_tuple(7, 2.718, "Matrix"));

        // Process different types of data
        process_data(100);
        process_data(3.1415);
        process_data(std::string("Hello"));

        std::complex<double> c(3.0, 4.0);
        process_data(c);

        // Compute all elements
        sci_container.compute_all();

        // Print metadata
        sci_container.print_metadata();

        // Filter elements using a lambda
        sci_container.filter_elements([](const int& key) { return key % 2 == 0; });

        // Range-based iteration
        for (const auto& [key, obj] : sci_container) {
            std::cout << "Iterating over key: " << key << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Exception caught in main: " << e.what() << std::endl;
    }

    return 0;
}
