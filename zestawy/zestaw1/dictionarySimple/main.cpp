#include "dict_simple.h"
#include <chrono>
#include <iostream>
#include <fstream>

#define NUM_ITERATIONS 100
#define NUM_REPEATS 100

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
    std::ofstream results_file("results.dat");
    if (!results_file)
    {
        std::cerr << "Nie można otworzyć pliku results.dat do zapisu!" << std::endl;
        return;
    }

    for (int i = 0; i < NUM_REPEATS; i++)
    {
        SimpleDict A;
        for (int j = 0; j < i; j++)
        {
            A.push("Element " + std::to_string(j));
        }

        double avg_push = measure_time([&A]()
                                       { A.push("Extra Element"); },
                                       [&A]()
                                       { A.pop("Extra Element"); });
        A.push("Extra Element");

        double avg_includes = measure_time([&A]()
                                           { A.includes("Extra Element"); });

        double avg_pop = measure_time([&A]()
                                      { A.pop("Extra Element"); },
                                      [&A]()
                                      { A.push("Extra Element"); });
        A.pop("Extra Element");

        results_file << i << " " << avg_push << " " << avg_includes << " " << avg_pop << "\n";
    }
    results_file.close();
}

void test_correctness()
{
    SimpleDict A;
    std::cout << "Testing correctness of operations:\n";
    A.display();
    A.push("Test Element");
    std::cout << "Push\n";
    A.display();
    if (A.includes("Test Element"))
        std::cout << "Push and Includes: PASS\n";
    else
        std::cout << "Push and Includes: FAIL\n";

    A.pop("Test Element");
    std::cout << "Pop\n";
    A.display();
    if (!A.includes("Test Element"))
        std::cout << "Pop: PASS\n";
    else
        std::cout << "Pop: FAIL\n";
}

int main()
{
    test_operations();
    system("gnuplot plot.gnu");
    test_correctness();
    return 0;
}