#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

void insert_sort(std::list<int>& arr, int val)
{
    auto where = std::find_if(arr.begin(), arr.end(), [val](int num){return num > val;});
    arr.insert(where, val);
}

void bucket_sort(std::vector<int>& arr)
{
    size_t sz = arr.size();
    auto max_el = *std::max_element(arr.begin(), arr.end()) + 1;
    std::vector<std::list<int>> temp(sz);
    for(auto it = arr.begin(); it != arr.end(); ++it)
    {
        size_t idx = (*it * sz)/max_el;
        insert_sort(temp[idx], *it);
    }
    arr.clear();

    for(auto it = temp.begin(); it != temp.end(); ++it)
    {
        arr.insert(arr.end(), (*it).begin(), (*it).end());
    }
}

int main()
{
    std::vector<int> temp = {74, 11, 72, 33, 40, 28, 23, 17, 66, 61, 85, 5, 70, 76, 34, 93, 41, 14, 63, 49, 87, 38, 64, 10, 77, 75, 46, 15, 0, 1 ,67 ,39 ,62 ,31 ,95, 6, 22 ,21 ,20 ,83 ,13, 8, 73 ,18, 3, 57 ,36 ,55, 32, 48, 54, 71, 78, 35 ,60 ,58 ,7 ,9 ,92 ,27 ,97 ,25 ,30, 89, 43, 19, 56, 90, 12, 45, 65, 47, 68, 53, 29, 16, 82, 37, 50, 24, 51, 98, 96, 91, 4, 80 ,26 ,99 ,94 ,84 ,2 ,86,79,52,44,59,69,88,81,42};
    bucket_sort(temp);
    for(auto it = temp.begin(); it != temp.end(); ++it) std::cout << *it << " ";
    std::cout << std::endl;
}