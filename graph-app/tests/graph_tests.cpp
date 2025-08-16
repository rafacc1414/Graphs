#include "graph_core/GraphGenerator.hpp"
#include "graph_core/GraphStorage.hpp"
#include "api/GraphAPI.hpp"
#include <gtest/gtest.h>

TEST(GraphListTest, AddNodesAndEdges) {
    // Undirected graph
    AdjacencyListGraph<int> graph(false); 
    graph.addNode(0);
    graph.addNode(1);
    graph.addEdge(0, 1, 5);

    const auto& adj = graph.getAdjList();
    EXPECT_EQ(adj.at(0).size(), 1);
    EXPECT_EQ(adj.at(0)[0].first, 1);
    EXPECT_EQ(adj.at(0)[0].second, 5);

    // Because the graph is undirected, the reverse edge should also exist
    EXPECT_EQ(adj.at(1).size(), 1); 
    EXPECT_EQ(adj.at(1)[0].first, 0);
    EXPECT_EQ(adj.at(1)[0].second, 5);
}

TEST(GraphMatrixTest, AddNodesAndEdges) {
    AdjacencyMatrixGraph<int> graph(2, false);
    graph.addEdge(0, 1, 7);

    const auto& mat = graph.getMatrix();
    EXPECT_EQ(mat[0][1].value(), 7);
    EXPECT_EQ(mat[1][0].value(), 7); // no dirigido
}

TEST(GraphGeneratorTest, GenerateRandomGraph) {
    auto graph = GraphGenerator::generateAdjacencyListGraph<int>(5, 1.0, 1, 10, false);
    EXPECT_EQ(graph.getAdjList().size(), 5);
    // Con edgeProbability=1.0, todos deberían tener al menos una arista
    bool has_edges = false;
    for (auto& [_, neighbors] : graph.getAdjList()) {
        if (!neighbors.empty()) {
            has_edges = true;
            break;
        }
    }
    EXPECT_TRUE(has_edges);
}

TEST(GraphAPITest, SerializeDeserializeList) {
    AdjacencyListGraph<int> graph(false);
    graph.addNode(0, "A");
    graph.addNode(1, "B");
    graph.addEdge(0, 1, 3);

    auto j = GraphAPI::serialize(graph);
    auto newGraph = GraphAPI::deserializeList<int>(j);

    EXPECT_EQ(newGraph.getAdjList().at(0)[0].first, 1);
    EXPECT_EQ(newGraph.getAdjList().at(0)[0].second, 3);
    EXPECT_EQ(newGraph.getNodeLabels().at(0), "A");
    EXPECT_EQ(newGraph.getNodeLabels().at(1), "B");
}

TEST(GraphAPITest, SerializeDeserializeMatrix) {
    AdjacencyMatrixGraph<int> graph(2, false);
    graph.addEdge(0, 1, 4);

    auto j = GraphAPI::serialize(graph);
    auto newGraph = GraphAPI::deserializeMatrix<int>(j);

    EXPECT_EQ(newGraph.getMatrix()[0][1].value(), 4);
    EXPECT_EQ(newGraph.getMatrix()[1][0].value(), 4);
}