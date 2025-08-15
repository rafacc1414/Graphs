#include "graph_core/Graph.hpp"

#include <iostream>

Graph::Graph(bool directed) : directed_(directed) {}

void Graph::addNode(int id, const std::string_view label) {
    nodes_[id] = label;
}

void Graph::addEdge(int from, int to, double weight) {
    adjList_[from].push_back({to, weight});
    if (!directed_) {
        adjList_[to].push_back({from, weight});
    }
}

void Graph::printGraph() const {
    std::cout << "Graph representation:\n";
    for (const auto& [node, edges] : adjList_) {
        std::cout << node << " (" << nodes_.at(node) << ") -> ";
        for (const auto& [dest, weight] : edges) {
            std::cout << dest << " (" << nodes_.at(dest) << ")"
                      << " [w=" << weight << "]  ";
        }
        std::cout << "\n";
    }
}
