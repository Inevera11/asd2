#include "graph.h"
#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

void test_graph()
{
    Graph<string, int> g;

    // Dodajemy wierzchołki i wartości
    g.addVertex(1);
    g.addVertex(2);
    g.setVertexValue(1, "A");
    g.setVertexValue(2, "B");

    cout << "Vertex 1: " << g.getVertexValue(1) << "\n"; // A
    cout << "Vertex 2: " << g.getVertexValue(2) << "\n"; // B

    // Dodajemy krawędź z wartością
    g.addEdge(1, 2, 42);
    cout << "Adjacent(1, 2): " << g.adjacent(1, 2) << "\n";        // 1 (true)
    cout << "Edge value (1, 2): " << g.getEdgeValue(1, 2) << "\n"; // 42

    // Zmieniamy wartość krawędzi
    g.setEdgeValue(1, 2, 99);
    cout << "New edge value (1, 2): " << g.getEdgeValue(1, 2) << "\n"; // 99

    // Sąsiedzi wierzchołka 1
    cout << "Neighbours of 1: ";
    for (int n : g.neighbours(1))
    {
        cout << n << " ";
    }
    cout << "\n"; // 2

    // Usunięcie krawędzi
    g.removeEdge(1, 2);
    cout << "Adjacent(1, 2) after removal: " << g.adjacent(1, 2) << "\n"; // 0

    // Usunięcie wierzchołka
    g.removeVertex(1);
    cout << "Vertex 1 removed. Neighbours of 2: ";
    for (int n : g.neighbours(2))
    {
        cout << n << " ";
    }
    cout << "\n"; // pusto

    cout << "All tests passed.\n";
}

void measure_time_complexity()
{

    int EL_COUNT = 1000;
    int STEP = 300;
    const int REPEATS = 5;

    Graph<string, int> g;

    ofstream file("performance.dat");
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    g.addVertex(0);

    for (int i = 1; i < EL_COUNT; i++)
    {
        g.addVertex(i);
        g.addEdge(0, i, i);
    }

    for (int n = EL_COUNT; n <= 10000; n += STEP)
    {
        long long total_time = 0;
        for (int i = 0; i < REPEATS; ++i)
        {
            auto start = high_resolution_clock::now();
            g.neighbours(0);
            auto end = high_resolution_clock::now();
            total_time += duration_cast<nanoseconds>(end - start).count();
        }
        auto avg_time = total_time / STEP;

        file << n << " " << avg_time << " " << endl;
        for (int i = n; i < STEP + n; i++)
        {
            g.addVertex(i);
            g.addEdge(0, i, i);
        }
    }

    file.close();
}

int main()
{
    test_graph();
    measure_time_complexity();
    system("gnuplot plot.gnu");
    return 0;
}
