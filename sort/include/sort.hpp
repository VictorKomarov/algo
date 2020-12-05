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

// TODO::refactor this class (he does too many jobs)
class BinaryFile {
private:
    std::fstream file;
    size_t available_nums = 0;
    std::string name;
 
    std::vector<uint16_t> buff; // fixed size
    size_t cursor = 0;
    size_t real_buff_size = 0;
    void fill_buff();
    uint16_t read();
public:
    BinaryFile(std::string path);
    BinaryFile(std::string path, size_t buff);
    BinaryFile(BinaryFile&& b) = default; 
    ~BinaryFile();
    BinaryFile(const BinaryFile& buff) = delete;

    void push_back(uint16_t num);
    std::vector<uint16_t> read_bucket(size_t limit);
    void remove_file();
    bool is_end();
    bool empty();
    void pop();
    uint16_t front();
    void seek_to_begin();
};

BinaryFile::BinaryFile(std::string path):
    file(path, std::ios::binary | std::ios::in | std::ios::out | std::ios::app), name(std::move(path))
{
    file.seekg(0, file.end);
    available_nums = file.tellg() / sizeof(uint16_t);
    file.seekg(0, file.beg); 
}

BinaryFile::BinaryFile(std::string path, size_t buff_size):BinaryFile(std::move(path))
{
    buff.reserve(buff_size);
    fill_buff();
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
        bucket.push_back(read());
    }
    
    return bucket;
}

void BinaryFile::remove_file() { remove(name.c_str());}

bool BinaryFile::is_end(){return available_nums == 0;}

uint16_t BinaryFile::read()
{
    char byte_2[sizeof(uint16_t)];
    file.read(byte_2, sizeof(uint16_t));
    auto num = reinterpret_cast<uint16_t*>(byte_2);
    --available_nums;
    return *num;
}

void BinaryFile::fill_buff()
{
    size_t i = 0;
    while (!is_end() && (i < buff.size()))
    {
        buff[i] = read();
        ++i;
    }
    cursor = 0;
    real_buff_size = i;
}

bool BinaryFile::empty()
{
    return (cursor == real_buff_size) && is_end();
}

void BinaryFile::pop()
{
    ++cursor;
}

uint16_t BinaryFile::front()
{
    if (cursor == real_buff_size) fill_buff();
    return buff[cursor];
}

void BinaryFile::seek_to_begin()
{
    file.seekg(0, file.beg);
}