#include "set_hashed.h"
#include <chrono>
#include <iostream>
#include <fstream>

#define NUM_ITERATIONS 100
#define NUM_REPEATS 1000

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

void test_element_operations()
{
    std::ofstream results_file("elements.dat");
    if (!results_file)
    {
        std::cerr << "Nie można otworzyć pliku results.dat do zapisu!" << std::endl;
        return;
    }
    std::vector<int> buckets{1, NUM_REPEATS / 2, NUM_REPEATS};

    results_file << "idx\t1_push\t1_incl\t1_pop\t1/2_push 1/2_incl 1/2_pop max_push max_incl max_pop \n";
    for (int i = 0; i < NUM_REPEATS; i++)
    {
        results_file << i << "\t";
        for (int bucket : buckets)
        {
            SetHashed A(bucket);
            for (int j = 0; j < i; j++)
            {
                A.push(j);
            }

            double avg_push = measure_time([&A, &i]()
                                           { A.push(i); },
                                           [&A, &i]()
                                           { A.pop(i); });
            A.push(i);

            double avg_includes = measure_time([&A, &i]()
                                               { A.includes(i); });

            double avg_pop = measure_time([&A, &i]()
                                          { A.pop(i); },
                                          [&A, &i]()
                                          { A.push(i); });
            A.pop(i);

            results_file << avg_push << "\t" << avg_includes << "\t" << avg_pop << "\t";
        }
        results_file << "\n";
    }
    results_file.close();
}

void test_sets_operations()
{
    std::ofstream results_file("sets.dat");
    if (!results_file)
    {
        std::cerr << "Nie można otworzyć pliku results.dat do zapisu!" << std::endl;
        return;
    }
    std::vector<int> buckets{1, NUM_REPEATS / 2, NUM_REPEATS};

    results_file << "idx\t1_A+B\t1_A-B\t1_A*B\t1_A==B\t1/2_A+B\t1/2_A-B\t1/2_A*B\t1/2_A==B\tmx_A+B\tmx_A-B\tmx_A*B\tmx_A==B\t \n";
    for (int i = 0; i < NUM_REPEATS; i++)
    {
        results_file << i << "\t";
        for (int bucket : buckets)
        {
            SetHashed A(bucket);
            for (int j = 0; j < i; j++)
            {
                A.push(j);
            }

            double avg_sum = measure_time([&A]()
                                          { A + A; });

            double avg_diff = measure_time([&A]()
                                           { A - A; });

            double avg_mult = measure_time([&A]()
                                           { A *A; });
            double avg_eq = measure_time([&A]()
                                         { A == A; });

            results_file << avg_sum << "\t" << avg_diff << "\t" << avg_mult << "\t" << avg_eq << "\t";
        }
        results_file << "\n";
    }
    results_file.close();
}

void test_correctness()
{
    SetHashed A(3);
    std::cout << "Testing correctness of operations:\n";
    A.display();
    A.push(1);
    std::cout << "Push 1\n";
    A.display();
    if (A.includes(1))
        std::cout << "Push and Includes: PASS\n";
    else
        std::cout << "Push and Includes: FAIL\n";

    A.pop(1);
    std::cout << "Pop 1\n";
    A.display();
    if (!A.includes(1))
        std::cout << "Pop: PASS\n";
    else
        std::cout << "Pop: FAIL\n";
    A.push(1);
    A.push(2);
    SetHashed B(3);
    B.push(2);
    B.push(3);
    std::cout << "New A and B sets\n";
    A.display();
    B.display();
    SetHashed C;
    C = A + B;
    std::cout << "A + B\n";
    C.display();
    C = A * B;
    std::cout << "A * B\n";
    C.display();
    C = A - B;
    std::cout << "A - B\n";
    C.display();
    A.pop(2);
    bool eq = A == C;
    std::cout << "{1} == {1} " << eq << " \n";
}

int main()
{
    // test_element_operations();
    // test_sets_operations();
    // system("gnuplot plot_el.gnu");
    system("gnuplot plot_set.gnu");
    // test_correctness();
    return 0;
}