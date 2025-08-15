#include <iostream>
#include "graph_core/Graph.hpp"

int main() {
    Graph g(false);
    g.addNode(1, "A");
    g.addNode(2, "B");
    g.addNode(3, "C");

    g.addEdge(1, 2, 5.0);
    g.addEdge(2, 3, 2.0);

    g.printGraph();
    return 0;
}
