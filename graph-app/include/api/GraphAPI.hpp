#pragma once
#include <nlohmann/json.hpp>
#include "graph_core/Graph.hpp"


/**
 * @brief Provides JSON serialization and deserialization for Graph.
 */
class GraphAPI {
public:
    /**
     * @brief Serializes a Graph object to JSON.
     * @param graph The graph to serialize.
     * @return nlohmann::json representation of the graph.
     */
    static nlohmann::json serialize(const Graph& graph);

    /**
     * @brief Deserializes a Graph object from JSON.
     * @param j JSON object representing the graph.
     * @return Graph object.
     */
    static Graph deserialize(const nlohmann::json& j);
};
