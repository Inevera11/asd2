#include "graph.h"
#include <stack>
#include <map>

template <typename T, typename E>
void dfsTopoSort(const Graph<T, E> &graph, int v, std::unordered_set<int> &visited, std::stack<int> &result)
{
    visited.insert(v);
    for (int neighbor : graph.neighbours(v))
    {
        if (!visited.count(neighbor))
        {
            dfsTopoSort(graph, neighbor, visited, result);
        }
    }
    result.push(v); // dopisujemy po odwiedzeniu wszystkich dzieci
}

template <typename T, typename E>
std::vector<T> topologicalSort(const Graph<T, E> &graph)
{
    std::unordered_set<int> visited;
    std::stack<int> result;
    std::vector<T> sorted;

    // Iterujemy po wszystkich wierzchołkach
    for (const auto &[id, _] : graph.getVertexMap())
    {
        if (!visited.count(id))
        {
            dfsTopoSort(graph, id, visited, result);
        }
    }

    // Konwertujemy ID na wartości
    while (!result.empty())
    {
        sorted.push_back(graph.getVertexValue(result.top()));
        result.pop();
    }

    return sorted;
}

int main()
{
    Graph<std::string, std::string> pancakeGraph;

    // Definicje czynności
    pancakeGraph.setVertexValue(0, "Nagrzej patelnię");
    pancakeGraph.setVertexValue(1, "Zmień składniki (jajko, mleko, olej, proszek)");
    pancakeGraph.setVertexValue(2, "Wylej ciasto na gorącą patelnię");
    pancakeGraph.setVertexValue(3, "Podpiecz z drugiej strony");
    pancakeGraph.setVertexValue(4, "Podgrzej syrop klonowy");
    pancakeGraph.setVertexValue(5, "Zjedz naleśnik z syropem");

    for (int i = 0; i <= 5; ++i)
    {
        pancakeGraph.addVertex(i);
    }

    // Krawędzie — relacje zależności
    pancakeGraph.addEdge(0, 2); // nagrzej patelnię -> wylej ciasto
    pancakeGraph.addEdge(1, 2); // zmieszaj składniki -> wylej ciasto
    pancakeGraph.addEdge(2, 3); // wylej -> podpiecz
    pancakeGraph.addEdge(3, 5); // podpiecz -> zjedz
    pancakeGraph.addEdge(4, 5); // podgrzej syrop -> zjedz

    auto sorted = topologicalSort(pancakeGraph);

    std::cout << "Kolejność czynności:\n";
    for (const auto &step : sorted)
    {
        std::cout << "- " << step << "\n";
    }

    return 0;
}
