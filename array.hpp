#pragma once
#include <memory>
#include <functional>

size_t single_array(size_t size);
size_t vector_array(size_t size);
size_t factor_array(size_t size); 

template <typename T>
class Array{
public:
    Array(std::function<size_t(size_t)> fn);
    Array(std::function<size_t(size_t)> fn, size_t n);
    Array(std::function<size_t(size_t)> fn, size_t n, T init);
    ~Array();
    T& operator[] (size_t i);
    void add(T val);
    void add(size_t i, T val);
    size_t size();
    T remove(size_t i);
    void expand(size_t arr, T init);
private:
    T* new_array(size_t sz);
    T* array;
    size_t size_;
    size_t cap;
    std::function<size_t(size_t)> next_size;
};

using strategy = std::function<size_t(size_t)>;

template <typename T>
Array<T>::Array(strategy fn): array(nullptr), size_(0), cap(0), next_size(fn){}

template <typename T>
Array<T>::Array(strategy fn, size_t n):array(new T[n]), size_(n), cap(n), next_size(fn){}
    
template <typename T>   
Array<T>::Array(strategy fn, size_t n, T init): array(new T[n]), size_(n), cap(n), next_size(fn)
{
    for(size_t i = 0; i < n; ++i)
    {
        array[i] = init;
    }
}

template <typename T>
Array<T>::~Array()
{
    delete[] array;
}

template <typename T>
T& Array<T>::operator[](size_t i)
{
    return array[i];
}

template <typename T>
void Array<T>::add(T val)
{
    if (cap == size_) {
        cap = next_size(cap);
        auto new_arr = new_array(cap);
        delete [] array;
        array = new_arr;
    }
    array[size_++] = val;
}

template <typename T>
void Array<T>::add(size_t i, T val)
{
    if (i < size_){
        array[i] = val;
        return;
    }

    add(val); // strange strategy
}

template <typename T>
size_t Array<T>::size() {return size_;}

template <typename T>
T Array<T>::remove(size_t i)
{
    T removed = array[i];
    auto next = i + 1;
    while (next < size_)
    {
        array[next-1] = array[next];
        ++next;
    }
    --size_;
    return removed;
}

template <typename T>
T* Array<T>::new_array(size_t sz)
{
    T* n_array =  new T[sz];
    for(size_t i = 0; i < size_; ++i)
    {
        n_array[i] = array[i];
    }
    return n_array;
}

template <typename T>
void Array<T>::expand(size_t sz, T init)
{
    for(;size_ < sz; ++size_)
    {
        array[size_] = init;
    }
}

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
