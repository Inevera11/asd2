#include "graph.h"
#include <fstream>

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

    ofstream file("graph_template");
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return -1;
    }

    file << "digraph G {" << endl;
    std::unordered_set<std::string> added_edges;

    auto vertices = g.getAllVertecsWithValues();
    for (const auto &[u, u_val] : vertices)
    {
        auto neighbors = g.neighbours(u);
        for (int v : neighbors)
        {
            std::string edge_key = std::to_string(std::min(u, v)) + "-" + std::to_string(std::max(u, v));
            if (added_edges.count(edge_key) == 0)
            {
                auto v_val = g.getVertexValue(v);
                int edge_val = g.getEdgeValue(u, v);
                file << "    \"" << u_val << "\" -> \"" << v_val << "\" [label=" << edge_val << "];" << endl;
                added_edges.insert(edge_key);
            }
        }
    }
    file << "}" << endl;

    file.close();
    return 0;
}