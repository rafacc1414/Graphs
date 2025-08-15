#include "graph_core/GraphStorage.hpp"
#include "api/GraphAPI.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

int main() {
    // List Graph Example
    AdjacencyListGraph<> listGraph(true);
    listGraph.addNode(0, "A");
    listGraph.addNode(1, "B");
    listGraph.addEdge(0, 1, 3.5);

    nlohmann::json j = GraphAPI::serialize(listGraph);
    std::cout << j.dump(4) << std::endl;

    auto loadedList = GraphAPI::deserializeList<>(j);

    {
        std::ofstream file("data/list_graph.json");
        file << j.dump(4);
        std::cout << "Archivo 'data/list_graph.json' guardado.\n";
    }

    // Matrix Graph Example
    AdjacencyMatrixGraph<> matrixGraph(2, true);
    matrixGraph.addNode(0, "A");
    matrixGraph.addNode(1, "B");
    matrixGraph.addEdge(0, 1, 2.5);

    nlohmann::json jMatrix = GraphAPI::serialize(matrixGraph);
    std::cout << jMatrix.dump(4) << std::endl;
    auto loadedMatrix = GraphAPI::deserializeMatrix<>(jMatrix);

    // Guardar en data/matrix_graph.json
    {
        std::ofstream file("data/matrix_graph.json");
        file << jMatrix.dump(4);
        std::cout << "Archivo 'data/matrix_graph.json' guardado.\n";
    }

    // Output loaded graphs
    std::cout << "Loaded List Graph: " << loadedList.getAdjList().size() << " nodes." << std::endl;
    std::cout << "Loaded Matrix Graph: " << loadedMatrix.getNodeLabels().size() << " nodes." << std::endl;


    return 0;
}
