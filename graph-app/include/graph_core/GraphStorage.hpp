#pragma once
#include <vector>
#include <unordered_map>
#include <optional>
#include <string>
#include <string_view>

/**
 * @brief Stores a graph as an adjacency list, with optional node labels.
 */
template<typename Weight = double>
class AdjacencyListGraph {
public:
    explicit AdjacencyListGraph(bool directed = false) : directed_(directed) {}

    void addNode(int id, std::string_view label = "") {
        adj_list_[id]; // Ensure node exists
        node_labels_[id] = std::string(label);
    }

    void addEdge(int from, int to, std::optional<Weight> weight = std::nullopt) {
        adj_list_[from].emplace_back(to, weight.value_or(1));
        if (!directed_ && from != to)
            adj_list_[to].emplace_back(from, weight.value_or(1));
    }

    const std::unordered_map<int, std::vector<std::pair<int, Weight>>>& getAdjList() const {
        return adj_list_;
    }

    const std::unordered_map<int, std::string>& getNodeLabels() const {
        return node_labels_;
    }

    bool isDirected() const { return directed_; }

private:
    bool directed_;
    std::unordered_map<int, std::vector<std::pair<int, Weight>>> adj_list_;
    std::unordered_map<int, std::string> node_labels_;
};

/**
 * @brief Stores a graph as an adjacency matrix, with optional node labels.
 */
template<typename Weight = double>
class AdjacencyMatrixGraph {
public:
    explicit AdjacencyMatrixGraph(size_t n, bool directed = false)
        : directed_(directed), size_(n),
          matrix_(n, std::vector<std::optional<Weight>>(n, std::nullopt)),
          node_labels_(n) {}

    void addNode(int id, std::string_view label = "") {
        if (id >= 0 && static_cast<size_t>(id) < size_)
            node_labels_[id] = std::string(label);
    }

    void addEdge(int from, int to, std::optional<Weight> weight = std::nullopt) {
        matrix_[from][to] = weight.value_or(1);
        if (!directed_ && from != to)
            matrix_[to][from] = weight.value_or(1);
    }

    const std::vector<std::vector<std::optional<Weight>>>& getMatrix() const {
        return matrix_;
    }

    const std::vector<std::string>& getNodeLabels() const {
        return node_labels_;
    }

    bool isDirected() const { return directed_; }
    size_t size() const { return size_; }

private:
    bool directed_;
    size_t size_;
    std::vector<std::vector<std::optional<Weight>>> matrix_;
    std::vector<std::string> node_labels_;
};