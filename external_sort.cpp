#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <limits>
#include <sstream>
#include <cstdio>

constexpr int BUFF_SIZE = 4096;

class FileBuff{
public:
    FileBuff(const std::string& path, size_t buff_size) : size(buff_size), buff(buff_size), path(path)
    {
        file.open(path); // TODO::check file
        fill_buff();
    }

    void close()
    {
        file.close();
        remove(path.c_str());
    }

    bool empty() { return file.eof() && (cur == size);}

    int front()
    {
        if (cur == size) fill_buff();

        return buff[cur];
    }

    void pop(){++cur;}
private:
    void fill_buff()
    {
        cur = size;
        while (file && cur)
        {
            file >> buff[size - cur];
            --cur;
        }
        cur = 0;
    }

    size_t size;
    size_t cur = 0;
    std::ifstream file;
    std::vector<int> buff;
    const std::string& path;
};

// strange signature for external sort purpose
template<typename Buff>
std::vector<int> merge(std::vector<Buff> arrs)
{
    std::vector<int> result;
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
        result.push_back(min);
        arrs[min_id].pop();
    }
    
    for(auto& q : arrs)
    {
        while (!q.empty())
        {
            result.push_back(q.front());
            q.pop();
        }
        return result;
    }

    return result;
}

//more copy :,C
std::vector<int> sort(std::vector<int> arr)
{
   if (arr.size() <= 1)
      return arr;
 
   std::vector<int> left, right, result;
   size_t middle = (arr.size()+ 1) / 2;
 
   for (size_t i = 0; i < middle; i++) {
      left.push_back(arr[i]);
   }

   for (size_t i = middle; i < arr.size(); i++) {
      right.push_back(arr[i]);
   }
 
   left = sort(left);
   right = sort(right);

   std::vector<std::queue<int>> merged = {(left.begin(), left.end()), (right.begin(), right.end())};
   result = merge(merged); 
   return result;
}

std::string sort_and_save(std::vector<int>& buf, int ntn)
{
    buf = sort(buf);
    std::stringstream ss;
    ss << ntn << "_file";

    std::fstream file(ss.str(), std::fstream::in | std::fstream::out | std::fstream::trunc);
    for(size_t i = 0; i < buf.size(); ++i)
    {
        if (i != 0) file << " ";
        file << buf[i];
    }
    file.close();

    return ss.str();
}

bool read_buff(std::istream& in, std::vector<int>& result, int size)
{
    int n; 
    while (in >> n && size--)
        result.push_back(n);

    return !in.eof();
}

void external_sort(const std::string& path)
{
    std::ifstream src(path);
    if(!src.is_open()) return;

    std::vector<std::string> sorted_buckets;
    std::vector<int> buff;
    int ntn = 0;
    while (read_buff(src, buff, BUFF_SIZE))
    {
        auto sorted = sort_and_save(buff, ntn++);
        sorted_buckets.push_back(sorted);
    }

    std::vector<FileBuff> files;
    for(auto it = sorted_buckets.begin(); it != sorted_buckets.end(); ++it)
    {
        files.emplace_back(*it, BUFF_SIZE/sorted_buckets.size());
    }

    merge(files); // TODO::change merge to file
}