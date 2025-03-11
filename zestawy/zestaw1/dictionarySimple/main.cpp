#include "dict_simple.h"
#include <chrono>
#include <iostream>

#define NUM_ITERATIONS 100

// Pomiar czasu
double measure_time(std::function<void()> func, std::function<void()> balancing_func = []() {})
{
    double total_time = 0;
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        if (balancing_func)
            balancing_func();
        total_time += std::chrono::duration<double, std::micro>(end - start).count();
    }
    return total_time / NUM_ITERATIONS;
}

void test_operations()
{
    SimpleDict A;

    for (int i = 0; i < 5; i++)
    {
        A.push("Element " + std::to_string(i));
    }

    std::cout << "Zbiór A: ";
    A.display();

    double avg_time = measure_time([&A]()
                                   { A.push("Extra Element"); },
                                   [&A]()
                                   { A.pop("Extra Element"); });
    std::cout << "Czas wykonania A.push(): " << avg_time << " μs" << std::endl;
    A.push("Extra Element");
    std::cout << "Wynik: A ";
    A.display();

    avg_time = measure_time([&A]()
                            { A.includes("Extra Element"); });
    std::cout << "Czas wykonania A.includes(): " << avg_time << " μs" << std::endl;
    assert(A.includes("Extra Element"));

    avg_time = measure_time([&A]()
                            { A.pop("Extra Element"); },
                            [&A]()
                            { A.push("Extra Element"); });
    std::cout << "Czas wykonania A.pop(): " << avg_time << " μs" << std::endl;
    A.pop("Extra Element");
    std::cout << "Wynik: A ";
    A.display();
}

int main()
{
    test_operations();
    return 0;
}
