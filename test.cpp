#include <iostream>
#include <fstream>
#include "sort.hpp"
#include <string>
#include <dirent.h>
#include <algorithm>

using function_sort = std::function<void(std::vector<int>&)>;

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
    std::string directory = "tests";
    std::vector<std::string> subdirs{"0.random", "1.digits", "2.sorted", "3.revers"};
    std::vector<TestCase> tests{{"bucket_sort", bucket_sort}};
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
                sort.t_case(copy);
                if (copy != sorted_nums){
                    std::cout << "FAIL " << sort.name << " " << file << std::endl;
                } else {
                    std::cout << "OK " << sort.name << " " << file << std::endl;
                }
            }    
            f.close();
        }
    }
}
