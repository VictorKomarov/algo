#include <iostream>
#include <fstream>

int main()
{
    std::ifstream f("test", std::ios::binary);
    f.seekg(0, f.end);
    size_t size = f.tellg();
    f.seekg(0, f.beg);
    size /= 2;
    while (size--)
    {
        char byte2[2];
        f.read(byte2, 2);
        auto num = reinterpret_cast<uint16_t*>(byte2);
        std::cout << *num << std::endl;
    }
    
}