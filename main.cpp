#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ifstream f("numbersToSort", std::ios::binary);
    char hex, hex2;
    f >> hex >> hex2;

    std::cout << hex << hex2 << std::endl;
}
