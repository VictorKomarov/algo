#include <iostream>
#include <fstream>
#include "sort.hpp"
#include <string>
#include <dirent.h>
#include <algorithm>

using function_sort = std::function<std::vector<int>&(std::vector<int>&)>;

std::vector<std::string> test_file(const std::string& dir)
{
    std::vector<std::string> tests;
    DIR* dirp = opendir(dir.c_str());
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
        std::string test = dp->d_name;
        if (test.find(".in") != std::string::npos) {
            tests.push_back(dir+"/" + test);
        }
    }
    closedir(dirp);

    return tests;
}

struct TestCase {
    std::string name;
    function_sort t_case;
};

int main()
{
    /*std::string directory = "tests";
    std::vector<std::string> subdirs{"0.random", "1.digits", "2.sorted", "3.revers"};
    std::vector<TestCase> tests{{"selection_sort", selection_sort}, {"insert_sort", insert_sort}, {"shell_sort", shell_sort}, {"heap_sort", heap_sort}};
    for(auto& sub : subdirs)
    {
        auto files = test_file(directory + "/" + sub);
        auto file = files[0];
        for(auto file : files)
        {
            std::ifstream f(file);
            if (!f.is_open()) {
                std::cerr<<"can't open "<< file << std::endl;
                return 1;
            }

            int n;
            f >> n;
            std::vector<int> nums(n);
            for(auto& num : nums) f >> num;
            auto sorted_nums = nums;
            std::sort(sorted_nums.begin(), sorted_nums.end());

            for(auto sort : tests)
            {
                auto copy = nums;
                copy = sort.t_case(copy);
                if (copy != sorted_nums){
                    std::cout << "FAIL " << sort.name << " " << file << std::endl;
                } else {
                    std::cout << "OK " << sort.name << " " << file << std::endl;
                }
            }    
            f.close();
        }
    }*/

    std::vector<int>n {7,0,6,1,3,2,8,5,4,9};
    n = heap_sort(n);
    for(auto i : n) std::cout << i;
    std::cout << std::endl;
}
