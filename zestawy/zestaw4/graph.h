#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

template <typename T, typename E>
class Graph
{
private:
    std::unordered_map<int, T> vertex_values;
    std::unordered_map<int, std::unordered_map<int, E>> edge_values;
    std::unordered_map<int, std::unordered_set<int>> adjacency_list;

public:
    // Sprawdza, czy istnieje krawędź między x a y
    bool adjacent(int x, int y) const
    {
        auto it = adjacency_list.find(x);
        return it != adjacency_list.end() && it->second.count(y) > 0;
    }

    // Zwraca sąsiadów wierzchołka x
    std::vector<int> neighbours(int x) const
    {
        std::vector<int> result;
        if (adjacency_list.count(x))
        {
            for (int neighbor : adjacency_list.at(x))
            {
                result.push_back(neighbor);
            }
        }
        return result;
    }

    // Dodaje wierzchołek x
    void addVertex(int x)
    {
        if (!adjacency_list.count(x))
        {
            adjacency_list[x] = {};
        }
    }

    // Usuwa wierzchołek x
    void removeVertex(int x)
    {
        adjacency_list.erase(x);
        vertex_values.erase(x);
        edge_values.erase(x);

        // Usuń odniesienia do x z innych wierzchołków
        for (auto &[v, neighbors] : adjacency_list)
        {
            neighbors.erase(x);
            edge_values[v].erase(x);
        }
    }

    // Dodaje krawędź między x a y
    void addEdge(int x, int y, const E &value = E())
    {
        addVertex(x);
        addVertex(y);
        adjacency_list[x].insert(y);
        adjacency_list[y].insert(x);
        edge_values[x][y] = value;
        edge_values[y][x] = value;
    }

    // Usuwa krawędź między x a y
    void removeEdge(int x, int y)
    {
        adjacency_list[x].erase(y);
        adjacency_list[y].erase(x);
        edge_values[x].erase(y);
        edge_values[y].erase(x);
    }

    // Zwraca wartość skojarzoną z wierzchołkiem x
    T getVertexValue(int x) const
    {
        assert(vertex_values.count(x));
        return vertex_values.at(x);
    }

    // Kojarzy wartość z wierzchołkiem x
    void setVertexValue(int x, const T &value)
    {
        vertex_values[x] = value;
    }

    // Zwraca wartość skojarzoną z krawędzią x-y
    E getEdgeValue(int x, int y) const
    {
        assert(edge_values.count(x) && edge_values.at(x).count(y));
        return edge_values.at(x).at(y);
    }

    // Ustawia wartość skojarzoną z krawędzią x-y
    void setEdgeValue(int x, int y, const E &value)
    {
        assert(adjacent(x, y));
        edge_values[x][y] = value;
        edge_values[y][x] = value; // nieskierowany graf
    }
};

#endif // GRAPH_H
