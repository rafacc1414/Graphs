#pragma once
#include "graph_core/GraphStorage.hpp"
#include "graph_core/algorithms.hpp"
#include <nlohmann/json.hpp>
#include <crow.h>

/**
 * @brief Provides JSON serialization and deserialization for different graph representations.
 */
class GraphAPI {
public:
    static void registerEndpoints(crow::SimpleApp& app);

    //
    // Adjacency List
    //
    template<typename Weight = double>
    static nlohmann::json serialize(const AdjacencyListGraph<Weight>& graph) {
        nlohmann::json j;
        j["type"] = "list";
        j["directed"] = graph.isDirected();

        // Serialize nodes
        for (const auto& [id, label] : graph.getNodeLabels()) {
            j["nodes"].push_back({{"id", id}, {"label", label}});
        }

        // Serialize edges
        for (const auto& [from, neighbors] : graph.getAdjList()) {
            for (const auto& [to, weight] : neighbors) {
                if (graph.isDirected() || from < to) {
                    j["edges"].push_back({{"from", from}, {"to", to}, {"weight", weight}});
                }
            }
        }

        return j;
    }

    template<typename Weight = double>
    static AdjacencyListGraph<Weight> deserializeList(const nlohmann::json& j) {
        bool directed = j.at("directed").get<bool>();
        AdjacencyListGraph<Weight> graph(directed);

        for (const auto& node : j.at("nodes")) {
            graph.addNode(node.at("id").get<int>(), node.at("label").get<std::string>());
        }
        for (const auto& edge : j.at("edges")) {
            graph.addEdge(edge.at("from").get<int>(), edge.at("to").get<int>(), edge.at("weight").get<Weight>());
        }

        return graph;
    }

    //
    // Adjacency Matrix
    //
    template<typename Weight = double>
    static nlohmann::json serialize(const AdjacencyMatrixGraph<Weight>& graph){
        nlohmann::json j;
        j["type"] = "matrix";
        j["directed"] = graph.isDirected();
        j["size"] = graph.size();

        // Serialize node labels
        const auto& labels = graph.getNodeLabels();
        for (size_t i = 0; i < labels.size(); ++i) {
            j["nodes"].push_back({{"id", static_cast<int>(i)}, {"label", labels[i]}});
        }

        // Serialize edges
        const auto& matrix = graph.getMatrix();
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j2 = 0; j2 < matrix[i].size(); ++j2) {
                if (matrix[i][j2].has_value()) {
                    if (graph.isDirected() || i < j2) {
                        j["edges"].push_back({
                            {"from", static_cast<int>(i)},
                            {"to", static_cast<int>(j2)},
                            {"weight", matrix[i][j2].value()}
                        });
                    }
                }
            }
        }

        return j;
    }

    template<typename Weight = double>
    static AdjacencyMatrixGraph<Weight> deserializeMatrix(const nlohmann::json& j) {
        bool directed = j.at("directed").get<bool>();
        size_t n = j.at("size").get<size_t>();
        AdjacencyMatrixGraph<Weight> graph(n, directed);

        for (const auto& node : j.at("nodes")) {
            graph.addNode(node.at("id").get<int>(), node.at("label").get<std::string>());
        }
        for (const auto& edge : j.at("edges")) {
            graph.addEdge(edge.at("from").get<int>(), edge.at("to").get<int>(), edge.at("weight").get<Weight>());
        }

        return graph;
    }

    // --------- TraversalResult ↔ JSON ---------
    static nlohmann::json serialize(const TraversalResult& r) {
        nlohmann::json j;
        j["type"]   = "traversal";
        j["source"] = r.source;
        j["order"]  = r.order;

        j["parent"] = nlohmann::json::array();
        for (const auto& [u, p] : r.parent) j["parent"].push_back({{"node", u}, {"parent", p}});

        j["depth"] = nlohmann::json::array();
        for (const auto& [u, d] : r.depth)  j["depth"].push_back({{"node", u}, {"depth", d}});

        return j;
    }

    static TraversalResult deserializeTraversal(const nlohmann::json& j) {
        TraversalResult r;
        r.source = j.at("source").get<int>();
        r.order  = j.at("order").get<std::vector<int>>();

        for (const auto& kv : j.at("parent")) {
            r.parent[kv.at("node").get<int>()] = kv.at("parent").get<int>();
        }
        for (const auto& kv : j.at("depth")) {
            r.depth[kv.at("node").get<int>()] = kv.at("depth").get<int>();
        }
        return r;
    }

    // --------- DijkstraResult ↔ JSON ---------
    template<typename Weight = double>
    static nlohmann::json serialize(const DijkstraResult<Weight>& r) {
        nlohmann::json j;
        j["type"]   = "dijkstra";
        j["source"] = r.source;

        j["dist"] = nlohmann::json::array();
        for (const auto& [u, d] : r.dist) j["dist"].push_back({{"node", u}, {"dist", d}});

        j["parent"] = nlohmann::json::array();
        for (const auto& [u, p] : r.parent) j["parent"].push_back({{"node", u}, {"parent", p}});

        return j;
    }

    template<typename Weight = double>
    static DijkstraResult<Weight> deserializeDijkstra(const nlohmann::json& j) {
        DijkstraResult<Weight> r;
        r.source = j.at("source").get<int>();

        for (const auto& kv : j.at("dist")) {
            r.dist[kv.at("node").get<int>()] = kv.at("dist").get<Weight>();
        }
        for (const auto& kv : j.at("parent")) {
            r.parent[kv.at("node").get<int>()] = kv.at("parent").get<int>();
        }
        return r;
    }
};
