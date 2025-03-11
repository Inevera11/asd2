#ifndef DICTSIMPLE_H
#define DICTSIMPLE_H

#include <iostream> // std::cout, std::cerr
#include <vector>   // std::vector
#include <cassert>  // assert()
#include <string>
#include <sstream>

#define STR_SIZE 50
#define MAX_SIZE 200

class SimpleDict
{
private:
    std::string table[MAX_SIZE];

    int hash(const std::string &str)
    {
        int sum = 0;
        for (char c : str)
        {
            sum += c;
        }
        return sum % MAX_SIZE;
    }

    std::string format_string(const std::string &str)
    {
        std::string formatted = str;
        if (formatted.size() > STR_SIZE)
        {
            formatted = formatted.substr(0, STR_SIZE);
        }
        else if (formatted.size() < STR_SIZE)
        {
            formatted.append(STR_SIZE - formatted.size(), ' ');
        }
        return formatted;
    }

public:
    SimpleDict()
    {
        for (int i = 0; i < MAX_SIZE; ++i)
        {
            table[i] = "";
        }
    }
    ~SimpleDict() = default;

    // Konstruktor kopiujący
    SimpleDict(const SimpleDict &other)
    {
        for (int i = 0; i < MAX_SIZE; ++i)
        {
            table[i] = other.table[i];
        }
    }

    // Konstruktor przenoszący
    SimpleDict(SimpleDict &&other)
    {
        for (int i = 0; i < MAX_SIZE; ++i)
        {
            table[i] = std::move(other.table[i]);
            other.table[i] = "";
        }
    }

    // Operator przypisania kopiującego
    SimpleDict &operator=(const SimpleDict &other)
    {
        if (this != &other)
        {
            for (int i = 0; i < MAX_SIZE; ++i)
            {
                table[i] = other.table[i];
            }
        }
        return *this;
    }

    // Operator przypisania przenoszącego
    SimpleDict &operator=(SimpleDict &&other)
    {
        if (this != &other)
        {
            for (int i = 0; i < MAX_SIZE; ++i)
            {
                table[i] = std::move(other.table[i]);
                other.table[i] = "";
            }
        }
        return *this;
    }

    bool empty() const
    {
        for (std::string val : table)
            if (!val.empty())
                return false;
        return true;
    }

    // Zwraca liczbę elementów w zbiorze
    std::size_t size() const
    {
        std::size_t count = 0;
        for (std::string val : table)
            if (!val.empty())
                count++;
        return count;
    }

    void push(std::string item)
    {
        item = format_string(item);
        int idx = hash(item);

        if (table[idx].empty())
        {
            table[idx] = item;
        }
        else
        {
            std::ostringstream oss;
            oss << "Kolizja elementu '" << item << "' na pozycji " << idx << " - element nie dodany!";
            std::cerr << oss.str() << std::endl;
        }
    }

    void pop(std::string item)
    {
        item = format_string(item);
        int idx = hash(item);

        if (!table[idx].empty())
        {
            table[idx] = "";
        }
    }

    bool includes(std::string item)
    {
        item = format_string(item);
        int idx = hash(item);

        if (!table[idx].empty())
        {
            return true;
        }
        return false;
    }

    void clear()
    {
        for (int i = 0; i < MAX_SIZE; ++i)
        {
            table[i] = "";
        }
    }

    void display() const
    {
        std::cout << " SimpleDict { ";
        for (int i = 0; i < MAX_SIZE; i++)
        {
            if (!table[i].empty())
                std::cout << table[i] << " ";
        }
        std::cout << "}" << std::endl;
    }
};

#endif // DICTSIMPLE_H
