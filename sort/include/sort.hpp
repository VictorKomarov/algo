#pragma once
#include <vector>
#include <utility>
#include <functional>
#include <fstream>
#include <cstdio>

void selection_sort(std::vector<int>& arr);
void insert_sort(std::vector<int>& arr);
void shell_sort(std::vector<int>& arr);
void heap_sort(std::vector<int>& nums);
void bucket_sort(std::vector<int>& arr);
void external_sort(std::string path);

class BinaryFile {
private:
    std::fstream file;
    std::string name;
    size_t available_nums = 0;
public:
    BinaryFile(std::string path);
    ~BinaryFile();
    BinaryFile(const BinaryFile& buff) = delete;

    void push_back(uint16_t num);
    std::vector<uint16_t> read_bucket(size_t limit);
    void remove_file();
    std::string get_file_name();
    bool is_end();
};

BinaryFile::BinaryFile(std::string path):
    file(path, std::ios::binary | std::ios::in | std::ios::out | std::ios::app), name(std::move(path))
{
    file.seekg(0, file.end);
    available_nums = file.tellg() / sizeof(uint16_t);
    file.seekg(0, file.beg); 
}

BinaryFile::~BinaryFile() { file.close();}

void BinaryFile::push_back(uint16_t num)
{
    if (file) {
        file.write((char *)&num, sizeof(num));
    }
}

std::vector<uint16_t> BinaryFile::read_bucket(size_t limit)
{
    std::vector<uint16_t> bucket;
    limit = (available_nums > limit) ? limit : available_nums;
    while (limit--)
    {
        char byte_2[sizeof(uint16_t)];
        file.read(byte_2, sizeof(uint16_t));
        auto num = reinterpret_cast<uint16_t*>(byte_2);
        bucket.push_back(*num);
        --available_nums;
    }
    
    return bucket;
}

void BinaryFile::remove_file() { remove(name.c_str());}

std::string BinaryFile::get_file_name(){return name;}

bool BinaryFile::is_end(){return available_nums == 0;}