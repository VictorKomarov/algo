#include <iostream>
#include <functional>
#include <vector>

std::vector<int>& selection_sort(std::vector<int>& arr)
{
    for(size_t i = 0; i < arr.size(); ++i)
    {
        size_t min_idx = i;
        for(size_t j = i+1; j < arr.size(); ++j)
        {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        std::swap(arr[i], arr[min_idx]);
    }

    return arr;
}

std::vector<int>& insert_sort(std::vector<int>& arr)
{
    for(size_t i = 1; i < arr.size(); ++i)
    {
        size_t idx = i;
        while (idx > 0 && arr[idx] < arr[idx-1])
        {
            std::swap(arr[idx], arr[idx-1]);
            --idx;
        }       
    }

    return arr;
}


std::vector<int>& shell_sort(std::vector<int>& arr, std::function<int(int)> next_step, int step)
{
    while (step > 1)
    {
        for(int i = 0; i < step; ++i)
        {
            int groups = (arr.size() / step);
            int last_index = i + (step * (groups - 1));
            while (last_index != i)
            {
                if (arr[last_index] < arr[last_index-step]) std::swap(arr[last_index], arr[last_index-step]);
                last_index-=step;
            }
        }
        step = next_step(step);
    }
    
    return insert_sort(arr);
}

int del_2(int num)
{
    return num / 2;
}

int main()
{
    std::vector<int> num = {7,6,5,4,3,2,1,0};
    num = shell_sort(num, del_2, num.size()/2);
    for(int n : num) std::cout << n << " ";
    std::cout << std::endl;
}