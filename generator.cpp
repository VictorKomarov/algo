#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <fstream>

void print_usage()
{
    std::cout << "usage: gen -n {file_name} -s {1eN}"  << std::endl;  
    exit(1);
}

auto parse_size_file(const char* size)
{
    if (!strstr(size, "1e")) print_usage();
    auto p = atoi(&(size[2]));
    return pow(10, p);
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    if (argc < 5) {
        print_usage();
    }

    std::string path;
    size_t size = 0;
    for(auto i = 1; i < argc; ++i)
    {
        if(strcmp(argv[i], "-n") == 0 && (i+1) < argc) {
            path = argv[i+1];        
        } else if (strcmp(argv[i], "-s") == 0 && (i+1) < argc) {
            size = parse_size_file(argv[i+1]);
        }
    }   
    if (path == "" || size == 0) print_usage();

    std::cout << "Generate " << path << " file with " << size << " numbers" << std::endl;
    std::ofstream file(path, std::ios::binary | std::ios::trunc);
    if (!file) {
        std::cerr << "can't create file" << std::endl;
        exit(1);
    }

    while(size--)
    {
        int16_t num =  rand() % static_cast<int16_t>(INT16_MAX);
        file.write((char *)&num, sizeof(num));
    }
    file.close();
}