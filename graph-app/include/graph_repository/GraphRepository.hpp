#pragma once
#include "graph_core/GraphStorage.hpp"

#include <unordered_map>
#include <memory>
#include <stdexcept>

class GraphRepository {
private:
    int nextId = 0;
    std::unordered_map<int, std::shared_ptr<void>> graphs;

public:
    template<typename GraphT>
    int addGraph(GraphT&& graph) {
        int id = nextId++;
        graphs[id] = std::make_shared<GraphT>(std::move(graph));
        return id;
    }

    template<typename GraphT>
    GraphT& getGraph(int id) {
        auto it = graphs.find(id);
        if (it == graphs.end()) {
            throw std::runtime_error("Graph not found");
        }
        return *std::static_pointer_cast<GraphT>(it->second);
    }
};
