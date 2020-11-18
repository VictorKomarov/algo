#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

double iter_pow(double base, int pow)
{
    if (pow == 0) return 1;
    double temp = base;
    for(int i = 1; i < pow; ++i) base *= temp;

    return base;
}

double approximate_pow2(double base, int pow)
{
    if (pow == 0) return 1;
    int pow2_count = log2(base);
    for(int i = 1; i < pow2_count; ++i) base *=base;

    return base * iter_pow(base, pow-pow2_count);
}

// template for next task   
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

int main(int argc, char **argv)
{
    double base;
    int pow;
    std::string func_type;
    func_type = argv[1];
    base = atof(argv[2]);
    pow = atoi(argv[3]);

    if (func_type == "fast_pow") {
        std::cout << fast_pow(base, 1.0, pow) << std::endl;
    } else if (func_type == "approximate_pow2") {
        std::cout << approximate_pow2(base, pow) << std::endl;
    } else if (func_type == "iter_pow") {
         std::cout << iter_pow(base, pow) << std::endl;
    } else {
        std::cout << "UNKNOWN FUNC TYPE" << std::endl;
    }
}