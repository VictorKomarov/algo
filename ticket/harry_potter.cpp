#include <iostream>
#include <string>
#include <cmath>

bool cond1(int i, int j) {
    return i >= j;
}

bool cond2(int i, int j) {
    return i != j;
}

bool cond3(int i, int j) {
    return (i+j) != 24;
}

bool cond4(int i, int j) {
    return (i+j) > 29;
}

bool cond5(int i, int j) {
    return floor(j / 2) != i;
}

bool cond6(int i, int j) {
    return i > 10 && j > 10;
}

bool cond7(int i, int j) {
    return !(i > 15 && j > 15);
}

bool cond8(int i, int j) {
    return i != 0 && j != 0;
}

bool cond9(int i, int j) {
    return abs(j-i) < 10;
}

bool cond10(int i, int j) {
    return floor(j / (i + 1)) != 1;
}

bool cond11(int i, int j) {
    return i != 1 && j != 1 && i != 23 && j != 23;
}

bool cond12(int i, int j) {
    return !(i*i + j*j <= 400);
}


int main()
{
    for(size_t i = 0; i < 25; ++i)
    {
        for(size_t j = 0; j < 25; ++j) {
            std::string r = cond12(i,j) ?  "." : "#";
            std::cout << r;
        }
        std::cout << std::endl;
    }
}