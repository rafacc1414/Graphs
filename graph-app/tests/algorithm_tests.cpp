
#include "graph_core/GraphStorage.hpp"
#include "graph_core/Algorithms.hpp"
#include "api/GraphAPI.hpp"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using namespace std;

// ---------- TEST BFS ----------
TEST(AlgorithmsTest, BFSBasic) {
    AdjacencyListGraph<double> g;
    g.addEdge(0, 1, 1.0);
    g.addEdge(0, 2, 1.0);
    g.addEdge(1, 3, 1.0);
    g.addEdge(2, 3, 1.0);

    TraversalResult r = Algorithms::BFS(g, 0);

    // orden válido: 0 primero, después 1 y 2, y 3 al final
    EXPECT_EQ(r.order.front(), 0);
    EXPECT_EQ(r.depth.at(0), 0);
    EXPECT_EQ(r.depth.at(1), 1);
    EXPECT_EQ(r.depth.at(2), 1);
    EXPECT_EQ(r.depth.at(3), 2);

    // serialización
    nlohmann::json j = GraphAPI::serialize(r);
    TraversalResult r2 = GraphAPI::deserializeTraversal(j);
    EXPECT_EQ(r2.order, r.order);
    EXPECT_EQ(r2.depth, r.depth);
}

// ---------- TEST DFS ----------
TEST(AlgorithmsTest, DFSBasic) {
    AdjacencyListGraph<double> g;
    g.addEdge(0, 1, 1.0);
    g.addEdge(0, 2, 1.0);
    g.addEdge(1, 3, 1.0);
    g.addEdge(2, 3, 1.0);

    TraversalResult r = Algorithms::DFS(g, 0);

    // debe visitar todos los nodos
    EXPECT_EQ(r.order.size(), 4);
    EXPECT_NE(find(r.order.begin(), r.order.end(), 3), r.order.end());

    // serialización
    nlohmann::json j = GraphAPI::serialize(r);
    TraversalResult r2 = GraphAPI::deserializeTraversal(j);
    EXPECT_EQ(r2.order, r.order);
    EXPECT_EQ(r2.parent, r.parent);
}

// ---------- TEST Dijkstra ----------
TEST(AlgorithmsTest, DijkstraBasic) {
    AdjacencyListGraph<double> g;
    g.addEdge(0, 1, 4.0);
    g.addEdge(0, 2, 1.0);
    g.addEdge(2, 1, 2.0);
    g.addEdge(1, 3, 1.0);
    g.addEdge(2, 3, 5.0);

    auto r = Algorithms::Dijkstra(g, 0);

    // distancia esperada:
    // 0 -> 0
    // 1 -> 3 (0->2->1)
    // 2 -> 1
    // 3 -> 4 (0->2->1->3)
    EXPECT_DOUBLE_EQ(r.dist.at(0), 0.0);
    EXPECT_DOUBLE_EQ(r.dist.at(1), 3.0);
    EXPECT_DOUBLE_EQ(r.dist.at(2), 1.0);
    EXPECT_DOUBLE_EQ(r.dist.at(3), 4.0);

    // serialización
    nlohmann::json j = GraphAPI::serialize(r);
    auto r2 = GraphAPI::deserializeDijkstra<double>(j);
    EXPECT_EQ(r2.dist, r.dist);
    EXPECT_EQ(r2.parent, r.parent);
}

// ---------- TEST Dijkstra camino reconstruido ----------
TEST(AlgorithmsTest, DijkstraPathReconstruction) {
    AdjacencyListGraph<double> g;
    g.addEdge(0, 1, 1.0);
    g.addEdge(1, 2, 1.0);
    g.addEdge(2, 3, 1.0);

    auto r = Algorithms::Dijkstra(g, 0);
    auto path = Algorithms::ReconstructPath<double>(3, r.parent);

    std::vector<int> expected = {0, 1, 2, 3};
    EXPECT_EQ(path, expected);
}

// ---------- TEST Dijkstra distancias ----------  
TEST(AlgorithmsTest, DijkstraDistances) {
    AdjacencyListGraph<double> g;
    // Grafo:
    // 0 --1--> 1 --2--> 2
    // 0 --4--> 2
    g.addEdge(0, 1, 1.0);
    g.addEdge(1, 2, 2.0);
    g.addEdge(0, 2, 4.0);

    auto r = Algorithms::Dijkstra(g, 0);

    // Distancias mínimas esperadas desde el nodo 0
    std::unordered_map<int, double> expectedDistances = {
        {0, 0.0},  // distancia a sí mismo
        {1, 1.0},  // 0->1
        {2, 3.0}   // 0->1->2 es más corto que 0->2 directo
    };

    // Comprobar que todas las distancias coinciden
    for (const auto& [node, dist] : expectedDistances) {
        ASSERT_TRUE(r.dist.find(node) != r.dist.end());
        EXPECT_DOUBLE_EQ(r.dist[node], dist);
    }
}
