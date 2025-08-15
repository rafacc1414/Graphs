#pragma once
#include <vector>
#include <string>
#include <unordered_map>

/**
 * @brief Represents a directed or undirected graph.
 */
class Graph {
public:
    /**
     * @brief Constructs a Graph object.
     * @param directed If true, the graph is directed; otherwise, it is undirected.
     */
    Graph(bool directed = false);

    /**
     * @brief Adds a node to the graph.
     * @param id Unique identifier for the node.
     * @param label Label or name for the node.
     */
    void addNode(int id, std::string_view label);

    /**
     * @brief Adds an edge between two nodes.
     * @param from Source node ID.
     * @param to Destination node ID.
     * @param weight Weight of the edge (default is 1.0).
     */
    void addEdge(int from, int to, double weight = 1.0);

    /**
     * @brief Prints the graph representation to the console.
     */
    void printGraph() const;

private:
    bool directed_; ///< Indicates if the graph is directed.
    std::unordered_map<int, std::string> nodes_; ///< Map of node IDs to labels.
    std::unordered_map<int, std::vector<std::pair<int, double>>> adjList_; ///< Adjacency list: node ID to list of (neighbor, weight) pairs.
};
