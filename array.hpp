#pragma once
#include <memory>

template<typename T>
class IArray{
public:
    virtual void add(T val) = 0;
    virtual void add(size_t i, T val) = 0;
    virtual ~IArray() = 0;
    virtual T remove(size_t i) = 0;
    virtual size_t size() = 0;
    virtual T& operator[] (size_t i) = 0; 
};

size_t single_array(size_t size) {return size+1;}

size_t vector_array(size_t size)
{
    if(size == 0) return 1;
    return size+size;
}

size_t factor_array(size_t size) 
{
    if(size == 0) return 1;
    return size + ((size+1)*50/100);
}