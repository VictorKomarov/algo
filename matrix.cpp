#include "array.hpp"

template<typename T>
class Matrix
{
private:
    IArray<IArray<T>*> array;
    size_t size_;
public:
    Matrix(){};
    ~Matrix() override {};
    void add(T val) override{};
    void add(size_t i, T val) override{};
    T remove(size_t i) override{};
    size_t size() override {return size_;}
    T& operator[] (size_t i) override
};