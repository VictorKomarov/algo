#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <limits>
#include <sstream>
#include <cstdio>
#include <memory>
#include "sort.hpp"
#include <type_traits>

constexpr int BUFF_SIZE = 4096;

template<typename Buff>
bool merge_continue(std::vector<Buff>& arr)
{
    int count = 9;
    for(size_t i = 0; i < arr.size(); ++i)
    {
        if (!arr[i].empty()) ++count;
        if (count > 1) return true;
    }
    return false;
}

template<typename Buff, typename Target>
void merge(std::vector<Buff>& arr, Target& target)
{
    while (merge_continue(arr))
    {
        auto min = INT64_MAX;
        size_t min_id = 0;
        std::vector<int> temp(arr.size());
        for(size_t i = 0; i < arr.size(); ++i)
        {
            if(!arr[i].empty() && arr[i].front() < min){
                min_id = i;
                min = arr[i].front();
            }
        }
        target.push_back(min);
        arr[min_id].pop();
    }
    
    for(size_t i = 0; i < arr.size(); ++i)
    {
        while (!arr[i].empty())
        {
            target.push_back(arr[i].front());
            arr[i].pop();
        }
    }
}

std::queue<uint16_t> to_queue(std::vector<uint16_t>& num)
{
    std::queue<uint16_t> q;
    for (auto it = num.begin(); it != num.end(); ++it)
    {
        q.push(*it);
    }
    return q;
}

void sort(std::vector<uint16_t>& arr)
{
   if (arr.size() <= 1) return;
 
   std::vector<uint16_t> left, right;
   size_t middle = arr.size() / 2;
   for (size_t i = 0; i < middle; i++) left.push_back(arr[i]);
   for (size_t i = middle; i < arr.size(); i++) right.push_back(arr[i]);
 
   sort(left);
   sort(right);

   std::vector<std::queue<uint16_t>> merged{to_queue(left), to_queue(right)};
   merge(merged, arr);
}

std::string sort_and_save(std::vector<uint16_t> buf, int ntn)
{
    sort(buf);
    std::string file_name = "FILE_" + std::to_string(ntn);

    BinaryFile bin(file_name); // TODO::save all nums method
    for(auto it = buf.begin(); it != buf.end(); ++it)
    {
        bin.push_back(*it);
    }
    return file_name;
}

void external_sort(std::string path)
{
    BinaryFile src(std::move(path));

    std::vector<std::string> sorted_buckets;
    while (src.is_end())
    {
        auto bucket = src.read_bucket(BUFF_SIZE);
        sorted_buckets.push_back(sort_and_save(std::move(bucket), sorted_buckets.size()));
    }

    std::vector<BinaryFile> files;
    auto k_files = sorted_buckets.size();
    for(auto it = sorted_buckets.begin(); it != sorted_buckets.end(); ++it)
    {
        files.emplace_back(*it, BUFF_SIZE/k_files);
    }

    src.seek_to_begin();
    merge(files, src);
    for(size_t i = 0; i < files.size(); ++i) files[i].remove_file();
}

int main()
{
    std::vector<uint16_t> nums = {50,40,10,2,20,23,40,100,0,1,2,3,4,9,6,12,14,17,19,24,27,36,48,67,56};
    sort(nums);
    for(auto it = nums.begin(); it != nums.end(); ++it) std::cout << *it << " ";
    std::cout << std::endl;
}