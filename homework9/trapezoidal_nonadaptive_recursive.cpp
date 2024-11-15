#include <iostream>
#include <functional>

//----------------------------------------------------------------------

using Function = std::function<double(double)>;

double basicTrapezoidal(const Function &f, double a, double b)
{
    return 0.5 * (b - a) * (f(a) + f(b));
}

double trapezoidalRecursive(const Function &f, double a, double b, double tol, int maxDepth, int depth)
{
    if (depth >= maxDepth)
    {
        return basicTrapezoidal(f, a, b);
    }

    double c = (a + b) / 2;

    double one_trap = basicTrapezoidal(f, a, b);
    double two_trap = basicTrapezoidal(f, a, c) + basicTrapezoidal(f, c, b);

    double error = std::abs(two_trap - one_trap);

    if (error < tol)
    {
        return two_trap;
    }

    return trapezoidalRecursive(f, a, c, tol / 2, maxDepth, depth + 1) +
           trapezoidalRecursive(f, c, b, tol / 2, maxDepth, depth + 1);
}


//----------------------------------------------------------------------

int main()
{

	const Function& f  = [](double x) {return x * x; };

	double result = trapezoidalRecursive(f, 2, 10, 1.e-8, 7, 0);
    std::cout << "integral: " << result << std::endl;
    std::cout << "exact: " << (1000 - 2*2*2) / 3. << std::endl;
}
