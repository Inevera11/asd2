#include <iostream>
#include <cassert>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include "heap.h"

using namespace std;
using namespace std::chrono;

void test_push_and_pop_min()
{
    PriorityQ<int> pq;

    assert(pq.empty());

    // Wstawiamy elementy w losowej kolejności
    pq.push(5);
    pq.push(3);
    pq.push(9);
    pq.push(1);

    assert(pq.size() == 4);

    // Powinno zwracać i usuwać najmniejszy element
    int min1 = pq.pop_min();
    assert(min1 == 1);
    assert(pq.size() == 3);

    int min2 = pq.pop_min();
    assert(min2 == 3);
    assert(pq.size() == 2);

    int min3 = pq.pop_min();
    assert(min3 == 5);
    assert(pq.size() == 1);

    int min4 = pq.pop_min();
    assert(min4 == 9);
    assert(pq.empty());

    cout
        << "All push/pop_min tests passed.\n";
}

void measure_time_complexity()
{
    const int START = 1000;
    const int END = 10000000;
    const int STEP = 1000;
    const int REPEATS = 100;

    ofstream file("performance.dat");
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    PriorityQ<int> pq;

    for (int n = START; n <= END; n += STEP)
    {
        // Dodaj nowe elementy, by zwiększyć rozmiar kopca
        for (int i = pq.size(); i < n; ++i)
        {
            pq.push(i);
        }

        long long total_push = 0;
        long long total_pop = 0;

        for (int i = 0; i < REPEATS; ++i)
        {
            auto start = high_resolution_clock::now();
            int min = pq.pop_min();
            auto end = high_resolution_clock::now();
            total_pop += duration_cast<nanoseconds>(end - start).count();

            start = high_resolution_clock::now();
            pq.push(min);
            end = high_resolution_clock::now();
            total_push += duration_cast<nanoseconds>(end - start).count();
        }

        auto avg_push_time = total_push / REPEATS;
        auto avg_pop_time = total_pop / REPEATS;

        file << pq.size() << " " << avg_push_time << " " << avg_pop_time << endl;
    }

    file.close();
}

int main()
{
    srand(time(0));
    // test_push_and_pop_min();
    // measure_time_complexity();
    // system("gnuplot plot.gnu");
    return 0;
}
