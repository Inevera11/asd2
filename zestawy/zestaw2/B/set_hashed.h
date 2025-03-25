#ifndef SET_HASHED_H
#define SET_HASHED_H

#include <iostream>
#include <vector>
#include <cassert>
#include "set_linked.h"

class SetHashed
{
private:
    int bucket_count;
    std::vector<LinkedSet<int>> vec;

    int hash(int val) const
    {
        return val % bucket_count;
    }

public:
    SetHashed(int size = 10) : bucket_count(size), vec(size) {}
    ~SetHashed() = default;

    // Konstruktor kopiujący
    SetHashed(const SetHashed &other) : bucket_count(other.bucket_count), vec(other.vec) {}

    // Konstruktor przenoszący
    SetHashed(SetHashed &&other) : bucket_count(other.bucket_count), vec(std::move(other.vec)) {}

    // Operator przypisania kopiującego
    SetHashed &operator=(const SetHashed &other)
    {
        if (this != &other)
        {
            bucket_count = other.bucket_count;
            vec = other.vec;
        }
        return *this;
    }

    // Operator przypisania przenoszącego
    SetHashed &operator=(SetHashed &&other) noexcept
    {
        if (this != &other)
        {
            bucket_count = other.bucket_count;
            vec = std::move(other.vec);
        }
        return *this;
    }

    bool empty() const
    {
        for (const auto &bucket : vec)
        {
            if (!bucket.empty())
                return false;
        }
        return true;
    }

    void push(int item)
    {
        vec[hash(item)].push(item);
    }

    void pop(int item)
    {
        vec[hash(item)].pop(item);
    }

    bool includes(int item) const
    {
        return vec[hash(item)].includes(item);
    }

    void clear()
    {
        for (auto &bucket : vec)
        {
            bucket.clear();
        }
    }

    void display() const
    {
        for (size_t i = 0; i < vec.size(); ++i)
        {
            std::cout << "Bucket " << i << ":";
            vec[i].display();
        }
    }

    SetHashed operator+(const SetHashed &other) const
    {
        SetHashed result(bucket_count);
        for (size_t i = 0; i < bucket_count; ++i)
        {
            result.vec[i] = vec[i] + other.vec[i];
        }
        return result;
    }

    SetHashed operator*(const SetHashed &other) const
    {
        SetHashed result(bucket_count);
        for (size_t i = 0; i < bucket_count; ++i)
        {
            result.vec[i] = vec[i] * other.vec[i];
        }
        return result;
    }

    SetHashed operator-(const SetHashed &other) const
    {
        SetHashed result(bucket_count);
        for (size_t i = 0; i < bucket_count; ++i)
        {
            result.vec[i] = vec[i] - other.vec[i];
        }
        return result;
    }

    bool operator==(const SetHashed &other) const
    {
        return vec == other.vec;
    }
};

#endif // SET_HASHED_H
