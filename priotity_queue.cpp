#include "array.hpp"

template <typename T>
struct SimpleList // delete memory
{
    SimpleList *next;
    T val;
    void insert(T val)
    {
        SimpleList *add = this;
        while (add->next)
        {
            add = add->next;
        }
        add->next = new SimpleList(nullptr, val);
    }
    T pop()
    {
        T removed = val;
        this = next;
    }
};

template <typename T>
class PriotityQueue
{
private:
    Array<SimpleList<T>*> arr;
public:
    PriotityQueue();
    ~PriotityQueue();

    void enqueue(size_t pr, T val)
    {
        if  (pr < arr.size()) {
            if (!arr[pr]){
                arr[pr] = new SimpleList(nullptr, val);
            } else {
                arr[pr]->insert(val)
            }
        } else {
            arr.expand(pr, nullptr);
            arr[i] = new SimpleList(nullptr, val);
        }
    }

    T dequeue()
    {
        for(size_t i = 0; i < arr.size(); ++i)
        {
            if (arr[i]) {
                return arr[i].pop();
            }
        }
    }
};
