#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <cassert>
#include <utility>

template <typename T>
class PriorityQ
{
private:
    T *data;
    std::size_t capacity;
    std::size_t length;

    void resize()
    {
        capacity *= 2;
        T *new_data = new T[capacity];
        for (std::size_t i = 0; i < length; ++i)
        {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }

    int get_left_child_idx(int parent_idx) const { return 2 * parent_idx + 1; }
    int get_right_child_idx(int parent_idx) const { return 2 * parent_idx + 2; }
    int get_parent_idx(int idx) const { return (idx - 1) / 2; }

    void heapify(int idx)
    {
        int smallest = idx;
        int left = get_left_child_idx(idx);
        int right = get_right_child_idx(idx);

        if (left < length && data[left] < data[smallest])
            smallest = left;

        if (right < length && data[right] < data[smallest])
            smallest = right;

        if (smallest != idx)
        {
            std::swap(data[idx], data[smallest]);
            heapify(smallest);
        }
    }

public:
    PriorityQ(std::size_t init_capacity = 16)
        : capacity(init_capacity), length(0)
    {
        data = new T[capacity];
    }

    ~PriorityQ()
    {
        delete[] data;
    }

    bool empty() const { return length == 0; }

    std::size_t size() const { return length; }

    void push(const T &item)
    {
        if (length == capacity)
            resize();

        data[length] = item;
        int idx = length;
        ++length;

        while (idx > 0 && data[idx] < data[get_parent_idx(idx)])
        {
            std::swap(data[idx], data[get_parent_idx(idx)]);
            idx = get_parent_idx(idx);
        }
    }

    T pop_min()
    {
        assert(!empty());
        T min = data[0];
        data[0] = data[length - 1];
        --length;
        if (length > 0)
            heapify(0);
        return min;
    }

    void clear()
    {
        length = 0;
    }

    void display() const
    {
        std::cout << "PQ { ";
        for (std::size_t i = 0; i < length; ++i)
        {
            std::cout << data[i] << " ";
        }
        std::cout << "}" << std::endl;
    }
};

#endif // HEAP_H
