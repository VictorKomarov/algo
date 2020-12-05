#include <iostream>
#include <functional>
#include <cmath>
#include <vector>

void selection_sort(std::vector<int>& arr)
{
    for(size_t i = 0; i < arr.size(); ++i)
    {
        size_t min_idx = i;
        for(size_t j = i+1; j < arr.size(); ++j)
        {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        std::swap(arr[i], arr[min_idx]);
    }
}

void insert_sort(std::vector<int>& arr)
{
    for(size_t i = 1; i < arr.size(); ++i)
    {
        size_t idx = i;
        while (idx > 0 && arr[idx] < arr[idx-1])
        {
            std::swap(arr[idx], arr[idx-1]);
            --idx;
        }       
    }
}

int classic_policy(int prev){ return prev / 2; }

int knuth_policy(int prev) { return (prev-1) / 3; }

int hibbard_policy(int prev) { return (log2(prev) - 1); }

void shell_sort(std::vector<int>& arr)
{
    size_t step = classic_policy(arr.size());
    while (step > 1)
    {
        for(size_t i = 0; i < step; ++i)
        {
            size_t groups = (arr.size() / step);
            size_t last_index = i + (step * (groups - 1));
            while (last_index != i)
            {
                if (arr[last_index] < arr[last_index-step]) std::swap(arr[last_index], arr[last_index-step]);
                last_index-=step;
            }
        }
        step = classic_policy(step);
    }
 
    insert_sort(arr);
}

class Heap {
public:
    Heap(std::vector<int>& arr) : heap(arr)
    {
        end_of_heap = heap.size()-1;
        heapify();
    }

    void Sort()
    {
        while (end_of_heap > 0)
        {
            std::swap(heap[0], heap[end_of_heap--]);
            heapify();
        }
    }

private:
    void heapify()
    {
        for(size_t i = end_of_heap; i != 0; --i)
        {
            shift_up(i);
        }
    }

    void shift_up(size_t idx) 
    {
        while (idx != 0)
        {
            size_t p_id = parent(idx);
            if (heap[p_id] > heap[idx]) return;
            std::swap(heap[idx], heap[p_id]);
            down_node(idx);
        }
    }

    void down_node(size_t idx = 0)
    {
        while (idx < end_of_heap)
        {
            size_t from = idx;
            size_t left = left_child(from);
            size_t right = right_child(from);

            if (left < end_of_heap && heap[left] > heap[from]) from = left;
            if (right < end_of_heap && heap[right] > heap[from]) from = right;
            if (from == idx) return;

            std::swap(heap[from], heap[idx]);
            idx = from;
        }
    }

    size_t parent(size_t id)    {return (id - 1) / 2;}
    size_t left_child(size_t id)  {return 2 * id + 1;}
    size_t right_child(size_t id) {return 2 * id + 2;}

    std::vector<int>& heap;
    size_t end_of_heap;
};

void heap_sort(std::vector<int>& nums)
{
    Heap(nums).Sort();
}
