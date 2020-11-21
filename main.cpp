#include <iostream>
#include <functional>
#include <cmath>
#include <vector>

std::vector<int>& selection_sort(std::vector<int>& arr)
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

    return arr;
}

std::vector<int>& insert_sort(std::vector<int>& arr)
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

    return arr;
}


std::vector<int>& shell_sort(std::vector<int>& arr, std::function<int(int)> next_step, int step)
{
    while (step > 1)
    {
        for(int i = 0; i < step; ++i)
        {
            int groups = (arr.size() / step);
            int last_index = i + (step * (groups - 1));
            while (last_index != i)
            {
                if (arr[last_index] < arr[last_index-step]) std::swap(arr[last_index], arr[last_index-step]);
                last_index-=step;
            }
        }
        step = next_step(step);
    }
    
    return insert_sort(arr);
}

int classic_policy(int prev){ return prev / 2; }

int knuth_policy(int prev) { return (prev-1) / 3; }

int hibbard_policy(int prev) { return (log2(prev) - 1); }

class Heap {
public:
    Heap(std::vector<int>& arr) : heap(arr)
    {
        heapify();
        end_of_heap = heap.size()-1;
    }

    std::vector<int>& Sort()
    {
        while (end_of_heap > 0)
        {
            std::swap(heap[0], heap[end_of_heap]);
            --end_of_heap;
            down_vertex();
        }
        return heap;
    }

private:
    void heapify()
    {
        for(size_t i = heap.size()-1; i != 0; --i)
        {
            shift_up(i);
        }
    }

    void shift_up(size_t idx) 
    {
        while (idx > 0)
        {
            size_t p_id = parent(idx);
            if (heap[p_id] > heap[idx]) return;
            std::swap(heap[p_id], heap[idx]);
            idx = p_id;
        }
    }

    void down_vertex()
    {
        size_t idx = 0;
        while (idx < end_of_heap)
        {
            size_t go_to = idx;
            size_t left = left_child(go_to);
            size_t right = right_child(go_to);

            if (left < end_of_heap && heap[left] > heap[go_to]) go_to = left;
            if (right < end_of_heap && heap[right] > heap[go_to]) go_to = right;
            if (go_to == idx) return;

            std::swap(heap[go_to], heap[idx]);
            idx = go_to;
        }
    }

    size_t parent(size_t id)    {return (id - 1) / 2;}
    size_t left_child(size_t id)  {return 2 * id + 1;}
    size_t right_child(size_t id) {return 2 * id + 2;}

    std::vector<int>& heap;
    size_t end_of_heap;
};

int main()
{
    std::vector<int> num = {10,23,4,0,1,56,29,100,22,19,15,7,9};
    Heap heap(num);
    num = heap.Sort();
    for(int n : num) std::cout << n << " ";
    std::cout << std::endl;
}