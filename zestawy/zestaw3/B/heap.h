#ifndef HEAP_H
#define HEAP_H

#include <iostream> // std::cout, std::cerr
#include <vector>   // std::vector
#include <cassert>  // assert()
#include <utility>

template <typename T>
class PriorityQ
{
private:
    std::vector<int> vec;

public:
    bool empty() const
    {
        return vec.empty();
    }

    std::size_t size() const
    {
        return vec.size();
    }

    int get_left_child_idx(int parent_idx)
    {
        return 2 * parent_idx + 1;
    }

    int get_right_child_idx(int parent_idx)
    {
        return 2 * parent_idx + 2;
    }

    int get_parent_idx(int idx) const { return (idx - 1) / 2; }

    void heapify(int idx)
    // function that will fix punctual heap distortions
    {
        int smallest = idx;
        int left = get_left_child_idx(idx);
        int right = get_right_child_idx(idx);

        if (left < vec.size() && vec[left] < vec[smallest])
            smallest = left;

        if (right < vec.size() && vec[right] < vec[smallest])
            smallest = right;

        if (smallest != idx)
        {
            std::swap(vec[idx], vec[smallest]);
            heapify(smallest);
        }
    }

    void push(T item)
    {
        vec.push_back(item);
        int idx = vec.size() - 1;

        while (idx > 0 && vec[idx] < vec[get_parent_idx(idx)])
        {
            std::swap(vec[idx], vec[get_parent_idx(idx)]);
            idx = get_parent_idx(idx);
        }
    }

    T pop_min()
    {
        assert(!empty() && "PriorityQueue is empty!");
        T min = vec.front();
        vec[0] = vec.back();
        vec.pop_back();

        if (!vec.empty())
            heapify(0);

        return min;
    }

    void clear()
    {
        vec.clear();
    }

    void display() const
    {
        std::cout << " PQ { ";
        for (auto el : vec)
        {
            std::cout << " " << el << " ";
        }
        std::cout << "}" << std::endl;
    }
};

#endif // HEAP_H
