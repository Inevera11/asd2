#ifndef SIMPLESET_H
#define SIMPLESET_H

#include <iostream> // std::cout, std::cerr
#include <vector>   // std::vector
#include <cassert>  // assert()

#define MAX_N 100000

class SimpleSet
{
private:
    std::vector<bool> vec; // Wektor przechowujący zbiór jako tablicę booli

public:
    // Konstruktor domyślny: inicjalizuje wektor o rozmiarze MAX_N z wartościami false
    SimpleSet() : vec(MAX_N, false) {}
    ~SimpleSet() = default;

    // Konstruktor kopiujący
    SimpleSet(const SimpleSet &other) : vec(other.vec) {}

    // Konstruktor przenoszący
    SimpleSet(SimpleSet &&other) noexcept : vec(std::move(other.vec)) {}

    // Operator przypisania kopiującego
    SimpleSet &operator=(const SimpleSet &other)
    {
        if (this != &other)
        {
            vec = other.vec;
        }
        return *this;
    }

    // Operator przypisania przenoszącego
    SimpleSet &operator=(SimpleSet &&other) noexcept
    {
        if (this != &other)
        {
            vec = std::move(other.vec);
        }
        return *this;
    }

    bool empty() const
    {
        for (bool val : vec)
            if (val)
                return false;
        return true;
    }

    // Zwraca liczbę elementów w zbiorze
    std::size_t size() const
    {
        std::size_t count = 0;
        for (bool val : vec)
            if (val)
                count++;
        return count;
    }

    void push(int item)
    {
        assert(item >= 0 && item < MAX_N && "Element poza zakresem!");
        vec[item] = true;
    }

    void pop(int item)
    {
        assert(item >= 0 && item < MAX_N && "Element poza zakresem!");
        vec[item] = false;
    }

    bool includes(int item) const
    {
        assert(item >= 0 && item < MAX_N && "Element poza zakresem!");
        return vec[item];
    }

    void clear()
    {
        vec.assign(MAX_N, false);
    }

    void display() const
    {
        std::cout << " SimpleSet { ";
        for (int i = 0; i < MAX_N; i++)
        {
            if (vec[i])
                std::cout << i << " ";
        }
        std::cout << "}" << std::endl;
    }

    // Suma zbiorów (A + B)
    SimpleSet operator+(const SimpleSet &other) const
    {
        SimpleSet result;
        for (int i = 0; i < MAX_N; i++)
        {
            result.vec[i] = this->vec[i] || other.vec[i];
        }
        return result;
    }

    // Iloczyn zbiorów (A * B)
    SimpleSet operator*(const SimpleSet &other) const
    {
        SimpleSet result;
        for (int i = 0; i < MAX_N; i++)
        {
            result.vec[i] = this->vec[i] && other.vec[i];
        }
        return result;
    }

    // Roznica  zbiorów (A - B)
    SimpleSet operator-(const SimpleSet &other) const
    {
        SimpleSet result;
        for (int i = 0; i < MAX_N; i++)
        {
            result.vec[i] = this->vec[i] && !other.vec[i];
        }
        return result;
    }

    bool operator==(const SimpleSet &other) const
    {
        return this->vec == other.vec;
    }
};

#endif // SIMPLESET_H
