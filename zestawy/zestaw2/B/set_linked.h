#ifndef LINKEDSET_H
#define LINKEDSET_H

#include <iostream> // std::cout, std::cerr
#include <vector>   // std::vector
#include <cassert>  // assert()

#define MAX_N 100

template <typename T>
struct SingleNode
{
    T value;
    SingleNode *next;
    SingleNode *prev;
    SingleNode() : value(T()), next(nullptr), prev(nullptr) {}
    SingleNode(const T &item, SingleNode *next_ptr = nullptr, SingleNode *prev_ptr = nullptr) : value(item), next(next_ptr), prev(prev_ptr) {}
    ~SingleNode() {}
};

template <typename T>
class LinkedSet
{
private:
    SingleNode<T> *head;

public:
    // Konstruktor domyślny: inicjalizuje wektor o rozmiarze MAX_N z wartościami false
    LinkedSet() : head(nullptr) {}
    ~LinkedSet()
    {
        clear();
    }

    // Konstruktor kopiujący
    LinkedSet(const LinkedSet &other) : head(nullptr)
    {
        if (!other.empty())
        {
            head = new SingleNode<T>(other.head->value);
            SingleNode<T> *curr = head;
            SingleNode<T> *templateNode = other.head->next;
            while (templateNode)
            {
                curr->next = new SingleNode<T>(templateNode->value, nullptr, curr);
                curr = curr->next;
                templateNode = templateNode->next;
            }
        }
    }

    // Konstruktor przenoszący
    LinkedSet(LinkedSet &&other) : head(other.head)
    {
        other.head = nullptr;
    }

    // Operator przypisania kopiującego
    LinkedSet &operator=(const LinkedSet &other)
    {
        if (this != &other)
        {
            LinkedSet<T> temp(other);
            std::swap(head, temp.head);
            // The destructor of `temp` will clean up the old data of `*this`
        }

        return *this;
    }

    // Operator przypisania przenoszącego
    LinkedSet &operator=(LinkedSet &&other) noexcept
    {
        if (this != &other)
        {
            clear();
            head = other.head;
            other.head = nullptr;
        }

        return *this;
    }

    bool empty() const
    {
        return head == nullptr;
    }

    std::size_t size() const
    {
        std::size_t count = 0;
        SingleNode<T> *curr = head;
        while (curr != nullptr)
        {
            count++;
            curr = curr->next;
        }
        return count;
    }

    void push(T item)
    {
        if (includes(item))
            return;
        SingleNode<T> *prev = head;
        if (empty())
        {
            head = new SingleNode<T>(item);
            return;
        }
        if (item < head->value)
        {
            head = new SingleNode<T>(item, head);
            head->next->prev = head;
            return;
        }
        while (prev->next != nullptr && prev->next->value < item)
        {
            prev = prev->next;
        }
        SingleNode<T> *node = new SingleNode<T>(item);
        node->next = prev->next;
        node->prev = prev;
        prev->next = node;
        if (node->next != nullptr)
        {
            node->next->prev = node;
        }
    }

    void pop(T item)
    {
        SingleNode<T> *curr = head;
        while (curr != nullptr && curr->value != item)
        {
            curr = curr->next;
        }

        if (curr == nullptr)
            return;

        if (curr == head)
        {
            head = head->next;
            if (head)
                head->prev = nullptr;
        }
        else
        {
            curr->prev->next = curr->next;
            if (curr->next)
                curr->next->prev = curr->prev;
        }

        delete curr;
    }

    bool includes(int item) const
    {
        SingleNode<T> *curr = head;
        while (curr != nullptr)
        {
            if (curr->value == item)
            {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    void clear()
    {
        SingleNode<T> *curr = head;
        while (curr != nullptr)
        {
            SingleNode<T> *to_del = curr;
            curr = curr->next;
            delete to_del;
        }
        head = nullptr;
    }

    void display() const
    {
        std::cout << " LinkedSet { ";
        SingleNode<T> *curr = head;
        while (curr != nullptr)
        {
            std::cout << curr->value << " ";
            curr = curr->next;
        }
        std::cout << "}" << std::endl;
    }

    // Suma zbiorów (A + B)
    LinkedSet operator+(const LinkedSet &other) const
    {
        LinkedSet result;
        SingleNode<T> *new_head = new SingleNode<T>();

        SingleNode<T> *curr = new_head;
        SingleNode<T> *l = this->head;
        SingleNode<T> *r = other.head;

        while (l != nullptr && r != nullptr)
        {
            if (l->value <= r->value)
            {
                curr->next = new SingleNode<T>(l->value);

                if (l->value == r->value)
                {
                    r = r->next;
                }
                l = l->next;
            }
            else
            {
                curr->next = new SingleNode<T>(r->value);
                r = r->next;
            }
            curr->next->prev = curr;
            curr = curr->next;
        }
        while (l != nullptr)
        {
            curr->next = new SingleNode<T>(l->value);
            curr->next->prev = curr;
            curr = curr->next;
            l = l->next;
        }
        while (r != nullptr)
        {
            curr->next = new SingleNode<T>(r->value);
            curr->next->prev = curr;
            curr = curr->next;
            r = r->next;
        }

        result.head = new_head->next;
        delete new_head;
        return result;
    }

    // Iloczyn zbiorów (A * B)
    LinkedSet operator*(const LinkedSet &other) const
    {
        LinkedSet result;
        SingleNode<T> *new_head = new SingleNode<T>();

        SingleNode<T> *curr = new_head;
        SingleNode<T> *l = this->head;

        while (l != nullptr)
        {
            SingleNode<T> *r = other.head;
            while (r != nullptr && r->value <= l->value)
            {
                if (r->value == l->value)
                {
                    curr->next = new SingleNode<T>(l->value);
                    curr->next->prev = curr;
                    curr = curr->next;
                }
                r = r->next;
            }
            l = l->next;
        }

        result.head = new_head->next;
        delete new_head;
        return result;
    }

    // Roznica  zbiorów (A - B)
    LinkedSet operator-(const LinkedSet &other) const
    {
        LinkedSet result(*this);
        SingleNode<T> *curr = other.head;
        while (curr != nullptr)
        {
            result.pop(curr->value);
            curr = curr->next;
        }
        return result;
    }

    bool operator==(const LinkedSet &other) const
    {
        SingleNode<T> *l = this->head;
        SingleNode<T> *r = other.head;

        while (l != nullptr && r != nullptr)
        {
            if (l->value != r->value)
            {
                return false;
            }
            l = l->next;
            r = r->next;
        }
        if (l != r)
        {
            return false;
        }
        return true;
    }
};

#endif // LINKEDSET_H
