#include "api/GraphAPI.hpp"

nlohmann::json GraphAPI::serialize(const Graph& graph) {
    nlohmann::json j;
    j["directed"] = graph.isDirected();

    // Serialize nodes
    for (const auto& [id, label] : graph.getNodes()) {
        j["nodes"].push_back({{"id", id}, {"label", label}});
    }

    // Serialize edges
    for (const auto& [from, neighbors] : graph.getAdjList()) {
        for (const auto& [to, weight] : neighbors) {
            if (graph.isDirected() || from < to) { // avoid duplicates in undirected
                j["edges"].push_back({{"from", from}, {"to", to}, {"weight", weight}});
            }
        }
    }

    return j;
}

Graph GraphAPI::deserialize(const nlohmann::json& j) {
    bool directed = j.at("directed").get<bool>();
    Graph graph(directed);

    for (const auto& node : j.at("nodes")) {
        int id = node.at("id").get<int>();
        std::string label = node.at("label").get<std::string>();
        graph.addNode(id, label);
    }

    for (const auto& edge : j.at("edges")) {
        int from = edge.at("from").get<int>();
        int to = edge.at("to").get<int>();
        double weight = edge.at("weight").get<double>();
        graph.addEdge(from, to, weight);
    }

    return graph;
}
