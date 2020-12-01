#include "array.hpp"

template<typename T, size_t Size>
class Matrix
{
private:
    Array<Array<T>*> array;
    auto index(size_t i) {return (i / Size) > Size ? Size-1 : i / Size;}
public:
    Matrix(): array(single_array, Size)
    {
        for(size_t i = 0; i < Size; ++i)
        {
            array[i] = new Array<T>(single_array, Size);
        }
    };
    ~Matrix() 
    {
        for(size_t i = 0; i < Size; ++i)
        {
            if (array[i])
                array[i]->~Array();
                delete array[i];
        }
    }
    void add(T val)
    {
        array[Size-1]->add(val);
    }
    void add(size_t i, T val)
    {
        array[index(i)]->add(val, i % Size)
    }
    T remove(size_t i)
    {
        auto sz = size();
        T removed = array[index(i)][i % Size]; 
        auto next = i + 1;
        while (next < sz)
        {
            array[index(next-1)][(next-1)%Size] = array[index(next)][next % Size];
        }
        return removed;
    }
    size_t size() 
    {
        auto size_ = 0;
        for(size_t i = 0; i < Size; ++i)
        {
            size_ += array[i]->size();
        }

        return size_;
    }
    T& operator[] (size_t i)  
    {
        return array[index(i)][i % Size];
    }
};