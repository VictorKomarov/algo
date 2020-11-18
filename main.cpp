#include <iostream>
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


std::vector<int>& shell_sort(std::vector<int>& arr, size_t step)
{

    return insert_sort(arr);
}


int main()
{
    std::vector<int> num = {10,92,3,20,1,2,3,0,4,6,109,5,8};
    num = insert_sort(num);
    for(int n : num) std::cout << n << " ";
    std::cout << std::endl;
}