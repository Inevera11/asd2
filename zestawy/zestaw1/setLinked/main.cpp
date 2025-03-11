#include "set_linked.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

void measurePerformance()
{
    ofstream file("performance.dat");
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    ofstream file_operations("operations.dat");
    if (!file_operations)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    for (int n = 1000; n <= 10000; n += 300)
    {
        LinkedSet<int> setA, setB;
        for (int i = 0; i < n; ++i)
        {
            setA.push(rand());
            setB.push(rand());
        }

        auto start = high_resolution_clock::now();
        setA.push(rand());
        auto end = high_resolution_clock::now();
        auto push_time = duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        setA.pop(rand());
        end = high_resolution_clock::now();
        auto pop_time = duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        setA.includes(rand());
        end = high_resolution_clock::now();
        auto includes_time = duration_cast<microseconds>(end - start).count();

        file << n << " " << push_time << " " << pop_time << " " << includes_time << endl;

        start = high_resolution_clock::now();
        LinkedSet<int> set_union = setA + setB;
        end = high_resolution_clock::now();
        auto union_time = duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        LinkedSet<int> set_intersection = setA * setB;
        end = high_resolution_clock::now();
        auto intersection_time = duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        LinkedSet<int> set_difference = setA - setB;
        end = high_resolution_clock::now();
        auto difference_time = duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        bool is_equal = (setA == setB);
        end = high_resolution_clock::now();
        auto equality_time = duration_cast<microseconds>(end - start).count();

        file_operations << n << " " << union_time << " " << intersection_time << " " << difference_time << " " << equality_time << endl;
    }

    file.close();
    file_operations.close();
    system("gnuplot plot.gnu");
}

int main()
{

    LinkedSet<int> A, B;
    for (int i = 0; i < 5; i++)
    {
        A.push(i);
        B.push(i + 1);
    }
    A.display();
    B.display();
    LinkedSet<int> C = A + B;
    cout << "A + B result: " << endl;
    C.display();
    C = A - B;
    cout << "A - B result: " << endl;
    C.display();
    C = A * B;
    cout << "A * B result: " << endl;
    C.display();
    bool equal = A == B;
    cout
        << "A == B result: " << equal << endl;

    B.push(0);
    cout
        << "B.push(0) result: " << endl;
    B.display();

    B.pop(5);
    cout
        << "B.pop(5) result: " << endl;
    B.display();

    equal = A == B;
    cout
        << "A == B result: " << equal << endl;

    // measurePerformance();
    cout << "Performance plots generated: 'performance.png' and 'operations.png'" << endl;
    return 0;
}
