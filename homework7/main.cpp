#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <cmath>

// Enumeration for Node Types
enum class NodeType {
    CONSTANT,
    VARIABLE,
    OPERATOR
};

// Node Class
class Node {
public:
    NodeType type;
    double value; // For constants
    char variable; // For variables like 'x'
    char op; // For operators like '+', '-', '*'

    // Constructor for constant
    Node(double val) : type(NodeType::CONSTANT), value(val), left(nullptr), right(nullptr) {}

    // Constructor for variable
    Node(char var) : type(NodeType::VARIABLE), variable(var), left(nullptr), right(nullptr) {}

    // Constructor for operator
    Node(char operation, std::shared_ptr<Node> leftNode, std::shared_ptr<Node> rightNode)
        : type(NodeType::OPERATOR), op(operation), left(leftNode), right(rightNode) {}

    // Pointers to children nodes
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

// PolynomialBinaryTree Class
class PolynomialBinaryTree {
public:
    std::shared_ptr<Node> root;

    // Constructor
    PolynomialBinaryTree() : root(nullptr) {}

    // Method to add a node
    void addNode(std::shared_ptr<Node> newNode) {
        if (!root) {
            root = newNode;
        } else {
            // Placeholder for adding nodes to the tree
            // In practice, you would implement logic to place the node in the correct position
        }
    }

    // Differentiation method
    std::shared_ptr<Node> differentiate(std::shared_ptr<Node> node) {
        if (!node) return nullptr;

        switch (node->type) {
            case NodeType::CONSTANT:
                return std::make_shared<Node>(0.0);

            case NodeType::VARIABLE:
                return std::make_shared<Node>(1.0);

            case NodeType::OPERATOR:
                if (node->op == '+') {
                    return std::make_shared<Node>('+', differentiate(node->left), differentiate(node->right));
                } else if (node->op == '*') {
                    // Apply product rule: (f * g)' = f' * g + f * g'
                    auto leftDiff = differentiate(node->left);
                    auto rightDiff = differentiate(node->right);
                    auto leftProduct = std::make_shared<Node>('*', leftDiff, node->right);
                    auto rightProduct = std::make_shared<Node>('*', node->left, rightDiff);
                    return std::make_shared<Node>('+', leftProduct, rightProduct);
                }
                break;
        }
        return nullptr;
    }

    // Evaluation method
    double evaluate(std::shared_ptr<Node> node, double x) {
        if (!node) return 0.0;

        switch (node->type) {
            case NodeType::CONSTANT:
                return node->value;

            case NodeType::VARIABLE:
                return x;

            case NodeType::OPERATOR:
                if (node->op == '+') {
                    return evaluate(node->left, x) + evaluate(node->right, x);
                } else if (node->op == '*') {
                    return evaluate(node->left, x) * evaluate(node->right, x);
                }
                break;
        }
        return 0.0;
    }

    // Save results to file
    void saveResults(const std::string& filename, const std::shared_ptr<Node>& poly) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        outFile << "x\tP(x)\tP'(x)\tP''(x)\tP'''(x)\tP''''(x)\tP'''''(x)\n";
        for (int i = 0; i <= 100; ++i) {
            double x = 0.0 + 1.0 * i / 100.0;
            outFile << x;

            auto currentPoly = poly;
            for (int j = 0; j < 6; ++j) {
                double value = evaluate(currentPoly, x);
                outFile << "\t" << value;
                currentPoly = differentiate(currentPoly);
            }
            outFile << "\n";
        }
        outFile.close();
    }
};

// Function to define polynomial by zeros
std::shared_ptr<Node> definePolynomial(const std::vector<double>& zeros) {
    if (zeros.empty()) return nullptr;

    std::shared_ptr<Node> poly = std::make_shared<Node>(1.0);
    for (double zero : zeros) {
        auto term = std::make_shared<Node>('*', poly, std::make_shared<Node>('+', std::make_shared<Node>('x'), std::make_shared<Node>(-zero)));
        poly = term;
    }
    return poly;
}

int main() {
    // Define a polynomial with zeros at -0.86, -0.34, 0.34, 0.86
    std::vector<double> zeros = {-0.86, -0.34, 0.34, 0.86};
    auto polynomial = definePolynomial(zeros);

    // Create a polynomial binary tree
    PolynomialBinaryTree tree;
    tree.root = polynomial;

    // Save the polynomial and its derivatives to a file
    tree.saveResults("polynomial_evaluation.txt", tree.root);

    std::cout << "Polynomial and its derivatives saved to polynomial_evaluation.txt" << std::endl;
    return 0;
}
