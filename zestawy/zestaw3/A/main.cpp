#include <iostream>
#include <cassert>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include "priority_queue.h"

using namespace std;
using namespace std::chrono;

void test_insert_and_pop_min()
{
    PriorityQueue<int> pq;

    assert(pq.empty());

    // Wstawiamy elementy w losowej kolejności
    pq.insert(5);
    pq.insert(3);
    pq.insert(9);
    pq.insert(1);

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

    cout << "All insert/pop_min tests passed.\n";
}

void measure_time_complexity()
{

    int EL_COUNT = 1000;
    int STEP = 300;

    ofstream file("performance.dat");
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    PriorityQueue<int> pq;
    for (int i = 0; i < EL_COUNT; i++)
    {
        pq.insert(rand());
    }

    for (int n = EL_COUNT; n <= 10000; n += STEP)
    {

        auto start = high_resolution_clock::now();
        pq.insert(rand());
        auto end = high_resolution_clock::now();
        auto insert_time = (end - start).count();

        start = high_resolution_clock::now();
        pq.pop_min();
        end = high_resolution_clock::now();
        auto pop_time = (end - start).count();

        // add another element in place popped one
        pq.insert(rand());

        file << n << " " << insert_time << " " << pop_time << " " << endl;
        for (int i = 0; i < STEP; i++)
        {
            pq.insert(rand());
        }
    }

    file.close();
}

int main()
{
    // test_insert_and_pop_min();
    // measure_time_complexity();
    system("gnuplot plot.gnu");
    return 0;
}
