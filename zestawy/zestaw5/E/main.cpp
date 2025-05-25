#include "graph.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <queue>

using namespace std;
using namespace std::chrono;

void draw_collision_graph(Graph<string, int> *g)
{

    std::vector<string> vertexes = {"AB", "AC", "AD", "BA", "BC", "BD", "DA", "DB", "DC", "EA", "EB", "EC", "ED"};
    std::unordered_map<int, std::unordered_set<int>> collisions = {
        {0, {4, 5, 6, 7, 8, 9, 10, 11, 12}},
        {1, {4, 5, 6, 7, 8, 9, 10, 11, 12}},
        {2, {4, 5, 9, 10, 11, 12}},
        {3, {9}},
        {4, {0, 1, 2, 6, 7, 8, 9, 10, 11, 12}},
        {5, {0, 1, 2, 6, 7, 9, 10, 11, 12}},
        {6, {0, 1, 3, 4, 5, 9, 10, 11}},
        {7, {0, 1, 4, 5, 10, 11}},
        {8, {1, 4, 10, 11}},
        {9, {0, 1, 2, 3, 4, 5, 6, 7, 8}},
        {10, {0, 1, 2, 4, 5, 6, 7, 8}},
        {11, {0, 1, 2, 4, 5, 6, 7, 8}},
        {12, {0, 1, 2, 4, 5}},

    };

    // Dodajemy wierzchołki i wartości
    for (int i = 0; i < vertexes.size(); i++)
    {
        g->addVertex(i);
        g->setVertexValue(i, vertexes[i]);
    }

    // Dodajemy krawędzie
    for (const auto &[from, neighbors] : collisions)
    {
        for (int to : neighbors)
            g->addEdge(from, to, 1);
    }
}

void colour_graph_bfs(Graph<string, int> *g, std::vector<int> *colored, std::queue<int> *to_visit)
{
    int vertex = to_visit->front();
    std::unordered_set<int> unavailable_colors;

    for (auto el : g->neighbours(vertex))
    {
        if (colored->at(el) >= 0)
        {
            unavailable_colors.insert(colored->at(el));
        }
        else
        {
            to_visit->push(el);
        }
    }

    int color = 0;
    while (unavailable_colors.contains(color))
    {
        color++;
    }
    colored->at(vertex) = color;
    g->setVertexColor(vertex, color);
    to_visit->pop();
}

void find_min_fazes(Graph<string, int> *g)
{
    std::vector<int> colored = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    std::queue<int> to_visit;
    to_visit.push(0);

    while (!to_visit.empty())
        colour_graph_bfs(g, &colored, &to_visit);

    int fazes = 0;
    for (auto color : colored)
    {
        fazes = max(fazes, color);
    }

    cout << "Min liczba znalezionych faz: " << fazes + 1 << endl;
};

int main()
{
    Graph<string, int> g;
    draw_collision_graph(&g);
    find_min_fazes(&g);
    g.exportToDotFile("collision_graph.txt");
    return 0;
}
