#include <iostream>
#include <cstdlib>
#include <cmath>

template<typename T>
T fast_pow(T base, T first, int pow)
{
    while (pow > 0)
    {
        if (pow%2) first = first * base;
        base = base * base;
        pow /= 2;
    }

    return first;
}

class FibbMatrix
{
public:
    FibbMatrix(double l1, double l2, double l3, double l4):_11(l1), _12(l2), _21(l3), _22(l4){}
    FibbMatrix():FibbMatrix(1,1,1,0){}

    FibbMatrix operator * (const FibbMatrix& p)
    {
        return 
        {
            _11*p._11 + _12*p._21,    _11*p._12 + _12*p._22,
            _21*p._11 + _22*p._21,    _21*p._12 + _22*p._22,
        };
    }

    double N() const
    {
        return _11;
    }
private:
    double _11, _12, _21, _22;
};


double fib_matrix(double n)
{
    if (n == 0 ) return 0;
    if (n  < 3) return 1;
    if (n == 3) return 2;
    return fast_pow(FibbMatrix(), FibbMatrix(), n-2).N();
}

double fib_rec(double n)
{
    if (n == 0) return 0;
    if (n <= 2) return 1;

    return fib_rec(n-1) + fib_rec(n-2);
}

double fib_iter(double n)
{
    double a1 = 0;
    double a2 = 1;
    for(double i = 0; i < n; ++i)
    {
        double temp = a1;
        a1 += a2;
        a2 = temp;
    }

    return a1;
}

double gold(int n) {
    double f = (1 + std::sqrt(5)) / 2;
    return std::floor(std::pow(f, n) / std::sqrt(5) + .5);
}

int main(int argc, char **argv)
{
    std::string func_type = argv[1];
    double n = atoi(argv[2]);

    if (func_type == "iter") {
        std::cout << fib_iter(n) << std::endl;
    } else if (func_type == "rec") {
        std::cout << fib_rec(n) << std::endl;
    } else if (func_type == "matrix") {
         std::cout << fib_matrix(n) << std::endl;
    } else if (func_type == "gold") {
         std::cout << fib_matrix(n) << std::endl;
    }  else {
        std::cout << "UNKNOWN FUNC TYPE" << std::endl;
    }
}