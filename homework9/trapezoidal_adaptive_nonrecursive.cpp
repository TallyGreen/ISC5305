#include <functional>
#include <iostream>

using Function = std::function<double(double)>;

struct Interval
{
	double a, b;
	double fa, fb, fm; // Added fm for midpoint
	double area;
	int depth;
};


double adaptiveTrapezoidalNonRecursive(const Function &f, double a, double b, double tolerance, int max_depth)
{
    //std::cout << "Starting nonRecursive with max_depth=" << max_depth
              //<< ", tolerance=" << tolerance << "\n";

    std::vector<Interval> intervals;
    double total_area = 0.0;

    // Initial interval
    double fa = f(a);
    double fb = f(b);

    Interval initial;
    initial.a = a;
    initial.b = b;
    initial.fa = fa;
    initial.fb = fb;
    initial.area = 0.5 * (b - a) * (fa + fb);
    initial.depth = 0;

    intervals.push_back(initial);

    while (!intervals.empty())
    {
        Interval interval = intervals.back();
        intervals.pop_back();

        //std::cout << "Processing depth " << interval.depth
                  //<< "/" << max_depth << " interval [" << interval.a << "," << interval.b << "]\n";

        if (interval.depth >= max_depth) // Back to >= but ensure max_depth > 0
        {
            //std::cout << "MAX DEPTH: Adding " << interval.area << "\n";
            total_area += interval.area;
            continue;
        }

        double mid = (interval.a + interval.b) / 2;
        double f_mid = f(mid);

        Interval left, right;
        left.a = interval.a;
        left.b = mid;
        left.fa = interval.fa;
        left.fb = f_mid;
        left.area = 0.5 * (mid - interval.a) * (left.fa + left.fb);
        left.depth = interval.depth + 1;

        right.a = mid;
        right.b = interval.b;
        right.fa = f_mid;
        right.fb = interval.fb;
        right.area = 0.5 * (interval.b - mid) * (right.fa + right.fb);
        right.depth = interval.depth + 1;

        double error = std::abs(left.area + right.area - interval.area);

        if (error < tolerance)
        {
            total_area += left.area + right.area;
        }
        else
        {
            intervals.push_back(right);
            intervals.push_back(left);
        }
    }

    return total_area;
}

//----------------------------------------------------------------------

int main()
{

	const Function& f  = [](double x) {return x * x; };

	double result = adaptiveTrapezoidalNonRecursive(f, 2., 10., 1.e-7, 5);
    std::cout << "integral: " << result << std::endl;
    std::cout << "exact: " << (1000 - 2*2*2) / 3. << std::endl;
}

//----------------------------------------------------------------------
