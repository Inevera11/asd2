#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

template <typename T, typename E>
class Graph
{
private:
    std::unordered_map<int, T> vertex_values;     // Wartości wierzchołków
    std::unordered_map<int, int> vertex_index;    // Mapowanie wierzchołków na indeksy w macierzy
    std::vector<std::vector<E>> adjacency_matrix; // Macierz połączeń
    int vertex_count = 0;                         // Liczba wierzchołków

    int getVertexIndex(int x) const
    {
        assert(vertex_index.count(x)); // Sprawdzamy, czy wierzchołek istnieje w grafie
        return vertex_index.at(x);
    }

public:
    // Sprawdza, czy istnieje krawędź między x a y
    bool adjacent(int x, int y) const
    {
        int i = getVertexIndex(x);
        int j = getVertexIndex(y);
        return adjacency_matrix[i][j] != E(); // Sprawdzamy, czy krawędź istnieje
    }

    // Zwraca sąsiadów wierzchołka x
    std::vector<int> neighbours(int x) const
    {
        std::vector<int> result;
        int i = getVertexIndex(x);

        for (int j = 0; j < vertex_count; ++j)
        {
            if (adjacency_matrix[i][j] != E()) // Jeśli istnieje krawędź
            {
                result.push_back(j);
            }
        }
        return result;
    }

    // Dodaje wierzchołek x
    void addVertex(int x)
    {
        if (vertex_index.count(x))
            return; // Wierzchołek już istnieje

        vertex_index[x] = vertex_count;
        vertex_values[x] = T(); // Przypisanie domyślnej wartości

        // Powiększamy macierz połączeń
        for (auto &row : adjacency_matrix)
        {
            row.push_back(E()); // Dodajemy kolumnę
        }
        adjacency_matrix.push_back(std::vector<E>(vertex_count + 1, E())); // Dodajemy nowy wiersz
        ++vertex_count;
    }

    // Usuwa wierzchołek x
    void removeVertex(int x)
    {
        int idx = getVertexIndex(x);

        // Usuwamy wiersz i kolumnę
        adjacency_matrix.erase(adjacency_matrix.begin() + idx);
        for (auto &row : adjacency_matrix)
        {
            row.erase(row.begin() + idx);
        }

        vertex_index.erase(x);
        vertex_values.erase(x);

        // Przesuwamy indeksy
        for (auto &entry : vertex_index)
        {
            if (entry.second > idx)
                entry.second--;
        }
        --vertex_count;
    }

    // Dodaje krawędź między x a y
    void addEdge(int x, int y, const E &value = E())
    {
        addVertex(x);
        addVertex(y);
        int i = getVertexIndex(x);
        int j = getVertexIndex(y);
        adjacency_matrix[i][j] = value;
    }

    // Usuwa krawędź między x a y
    void removeEdge(int x, int y)
    {
        int i = getVertexIndex(x);
        int j = getVertexIndex(y);
        adjacency_matrix[i][j] = E(); // Usuwamy krawędź (ustawiamy domyślną wartość)
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
        int i = getVertexIndex(x);
        int j = getVertexIndex(y);
        return adjacency_matrix[i][j];
    }

    // Ustawia wartość skojarzoną z krawędzią x-y
    void setEdgeValue(int x, int y, const E &value)
    {
        int i = getVertexIndex(x);
        int j = getVertexIndex(y);
        adjacency_matrix[i][j] = value;
    }
};

#endif // GRAPH_H
