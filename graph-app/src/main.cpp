#include "graph_core/Graph.hpp"
#include "api/GraphAPI.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

int main() {
    Graph g(false); // false = no dirigido

    // Añadir nodos y aristas
    g.addNode(1, "Node 1");
    g.addNode(2, "Node 2");
    g.addNode(3, "Node 3");

    g.addEdge(1, 2, 1.5);
    g.addEdge(2, 3, 2.0);

    // Mostrar grafo
    g.printGraph();

    // Serializar con GraphAPI
    nlohmann::json j = GraphAPI::serialize(g);
    std::cout << j.dump(4) << std::endl;

    // Deserializar de nuevo (prueba)
    Graph g2 = GraphAPI::deserialize(j);
    g2.printGraph();

    return 0;
}
