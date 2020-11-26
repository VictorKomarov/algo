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
    std::vector<int> temp = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    bucket_sort(temp);
    for(auto it = temp.begin(); it != temp.end(); ++it) std::cout << *it << " ";
    std::cout << std::endl;
}