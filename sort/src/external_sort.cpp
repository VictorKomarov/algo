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

constexpr int BUFF_SIZE = 4096;

template<typename Buff, typename Target>
void merge(std::vector<Buff>& arrs, Target& target)
{
    while (std::count_if(arrs.begin(), arrs.end(), [](Buff q){return !q.empty();}) != 1)
    {
        auto min = INT64_MAX;
        size_t min_id = 0;
        std::vector<int> temp(arrs.size());
        for(size_t i = 0; i < arrs.size(); ++i)
        {
            if(!arrs[i].empty() && arrs[i].front() < min){
                min_id = i;
                min = arrs[i].front();
            }
        }
        target.push_back(min);
        arrs[min_id].pop();
    }
    
    for(size_t i = 0; i < arrs.size(); ++i)
    {
        while (!arrs[i].empty())
        {
            target.push_back(arrs[i].front());
            arrs[i].pop();
        }
    }
}

std::queue<int> to_queue(std::vector<uint16_t>& num)
{
    std::queue<int> q;
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
   size_t middle = (arr.size()+ 1) / 2;
   for (size_t i = 0; i < middle; i++) left.push_back(arr[i]);
   for (size_t i = middle; i < arr.size(); i++) right.push_back(arr[i]);
 
   sort(left);
   sort(right);

   std::vector<std::queue<int>> merged{to_queue(left), to_queue(right)};
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

    // seek to begin src
    merge(files, src);
}

int main()
{
}