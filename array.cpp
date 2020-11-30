#include "array.hpp"
#include <functional>
#include <cmath>

using strategy = std::function<size_t(size_t)>;

template <typename T>
class Array : public IArray {
public:
    Array(strategy fn): array(nullptr), size(0), cap(0), next_size(fn){};
    Array(strategy fn, size_t n, T init): array(new T[n]), size(n), cap(n), next_size(fn)
    {
        for(size_t i = 0; i < n; ++i)
        {
            array[i] = init;
        }
    }

    ~Array() override
    {
        delete [] array;
    }

    T& operator[](size_t i)
    {
        return array[i];
    }

    void add(T val) override
    {
        if (cap == size) {
            cap = next_size(cap);
            auto new_arr = new_array(cap);
            delete [] array;
            array = new_arr;
        }
        array[size_++] = val;
    }

    void add(size_t i, T val) override
    {
        if (i < size){
            array[i] = val;
            return;
        }

        add(val); // strange strategy
    }

    size_t size() override {return size_;}

    T remove(size_t i) override
    {
        T removed = array[i];
        auto next = i + 1;
        while (next < size)
        {
            array[next-1] = array[next];
            ++next;
        }
        --size;
        return removed;
    }

private:
    T* new_array(size_t sz)
    {
        T* n_array =  new T[sz];
        for(size_t i = 0; i < size_; ++i)
        {
            n_array[i] = array[i];
        }
        return n_array;
    }

    T* array;
    size_t size_;
    size_t cap;
    strategy next_size;
};