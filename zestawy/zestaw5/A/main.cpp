#include "graph.h"

using namespace std;

int main()
{
    Graph<string, int> g;

    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.setVertexValue(1, "A");
    g.setVertexValue(2, "B");
    g.setVertexValue(3, "C");

    // Dodajemy krawędź z wartością
    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 3);
    g.addEdge(3, 3, 1);

    g.exportToDotFile("graph_template");
    return 0;
}