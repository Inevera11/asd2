#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "set_linked.h"

template <typename T>
class PriorityQueue
{
private:
    LinkedSet<T> data;

public:
    PriorityQueue() {}

    void insert(const T &item)
    {
        data.push(item);
    }

    T pop_min()
    {
        assert(!data.empty() && "PriorityQueue is empty!");

        // Ponieważ LinkedSet przechowuje elementy rosnąco, pierwszy element to minimum
        SingleNode<T> *head = data.get_head();
        T min_val = head->value;
        data.pop(min_val);
        return min_val;
    }

    bool empty() const
    {
        return data.empty();
    }

    std::size_t size() const
    {
        return data.size();
    }

    void display() const
    {
        data.display();
    }
};

#endif // PRIORITY_QUEUE_H
