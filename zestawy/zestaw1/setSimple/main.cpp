#include "set_simple.h"
#include <chrono>

#define NUM_ITERATIONS 100

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
    SimpleSet A, B;
    for (int i = 0; i < 5; i++)
    {
        A.push(i);
        B.push(i + 1);
    }

    std::cout << "Zbiór A: ";
    A.display();
    std::cout << "Zbiór B: ";
    B.display();

    double avg_time = measure_time([&A, &B]()
                                   { A + B; });
    std::cout << "Czas wykonania (A + B): " << avg_time << " μs" << std::endl;

    avg_time = measure_time([&A, &B]()
                            { A *B; });
    std::cout << "Czas wykonania (A * B): " << avg_time << " μs" << std::endl;

    avg_time = measure_time([&A, &B]()
                            { A - B; });
    std::cout << "Czas wykonania (A - B): " << avg_time << " μs" << std::endl;

    avg_time = measure_time([&A, &B]()
                            { A == B; });
    std::cout << "Czas wykonania (A == B): " << avg_time << " μs result: " << (A == B) << std::endl;

    avg_time = measure_time([&B]()
                            { B.push(0); }, [&B]()
                            { B.pop(0); });
    std::cout << "Czas wykonania B.push(0): " << avg_time << " μs" << std::endl;
    B.push(0);
    std::cout
        << "Wynik: B ";
    B.display();

    avg_time = measure_time([&B]()
                            { B.pop(5); }, [&B]()
                            { B.push(5); });
    std::cout << "Czas wykonania B.pop(5): " << avg_time << " μs" << std::endl;
    B.pop(5);
    std::cout
        << "Wynik: B ";
    B.display();

    avg_time = measure_time([&A]()
                            { A.includes(2); });
    std::cout << "Czas wykonania A.includes(2): " << avg_time << " μs result: " << A.includes(2) << std::endl;

    bool equal = (A == B);
    std::cout << "Czy teraz A == B? " << (equal ? "Tak" : "Nie") << std::endl;
}

int main()
{
    test_operations();
    return 0;
}