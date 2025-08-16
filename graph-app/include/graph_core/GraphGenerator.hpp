#pragma once
#include <random>
#include <type_traits>
#include "GraphStorage.hpp"

template<typename T>
T randomWeight(T minWeight, T maxWeight) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(minWeight, maxWeight);
        return dist(gen);
    } else {
        std::uniform_real_distribution<T> dist(minWeight, maxWeight);
        return dist(gen);
    }
}

class GraphGenerator {
public:
    template<typename T>
    static AdjacencyListGraph<T> generateAdjacencyListGraph(
        size_t nodeCount,
        double edgeProbability,
        T minWeight,
        T maxWeight,
        bool directed
    ) {
        AdjacencyListGraph<T> graph(directed);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> probDist(0.0, 1.0);

        for (size_t i = 0; i < nodeCount; ++i) {
            graph.addNode(i);
        }

        for (size_t i = 0; i < nodeCount; ++i) {
            for (size_t j = (directed ? 0 : i + 1); j < nodeCount; ++j) {
                if (i != j && probDist(gen) < edgeProbability) {
                    T weight = randomWeight(minWeight, maxWeight);
                    graph.addEdge(i, j, weight);
                }
            }
        }

        return graph;
    }

    template<typename T>
    static AdjacencyMatrixGraph<T> generateAdjacencyMatrixGraph(
        size_t nodeCount,
        double edgeProbability,
        T minWeight,
        T maxWeight,
        bool directed
    ) {
        AdjacencyMatrixGraph<T> graph(nodeCount, directed);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> probDist(0.0, 1.0);

        for (size_t i = 0; i < nodeCount; ++i) {
            for (size_t j = (directed ? 0 : i + 1); j < nodeCount; ++j) {
                if (i != j && probDist(gen) < edgeProbability) {
                    T weight = randomWeight(minWeight, maxWeight);
                    graph.addEdge(i, j, weight);
                }
            }
        }

        return graph;
    }
};
