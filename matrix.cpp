#include <memory>
template<typename T>
class Array;

template<typename T>
class Matrix
{
private:
    Array<Array<T>> array;
    size_t arrs;
public:
    Matrix()
    {
        arrs = 10;
        array = new 
    };
    ~Matrix();
};