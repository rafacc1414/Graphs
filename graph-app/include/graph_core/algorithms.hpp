#pragma once
#include "GraphStorage.hpp"
#include <queue>
#include <stack>
#include <limits>
#include <unordered_map>
#include <vector>
#include <optional>
#include <iostream>

// ---------- Resultados estructurados ----------

struct TraversalResult
{
    int source = -1;
    std::vector<int> order;              // orden de visita
    std::unordered_map<int, int> parent; // padre de cada nodo (o -1)
    std::unordered_map<int, int> depth;  // distancia en saltos desde source
};

template <typename Weight>
struct DijkstraResult
{
    int source = -1;
    std::unordered_map<int, Weight> dist; // distancia mínima desde source
    std::unordered_map<int, int> parent;  // predecesor en el camino más corto
};

namespace Algorithms
{
    // ---------- BFS ----------

    template <typename Weight = double>
    TraversalResult BFS(const AdjacencyListGraph<Weight> &graph, int source)
    {
        TraversalResult result;
        result.source = source;

        std::queue<int> fifo_queue;
        std::unordered_map<int, bool> seen;

        // inicialización
        for (const auto &[id, _] : graph.getAdjList())
        {
            result.parent[id] = -1;
            result.depth[id] = std::numeric_limits<int>::max();
        }
        if (!graph.getAdjList().count(source))
            return result;

        seen[source] = true;
        result.depth[source] = 0;
        fifo_queue.push(source);

        while (!fifo_queue.empty())
        {
            int visiting_node = fifo_queue.front();
            fifo_queue.pop();
            result.order.push_back(visiting_node);
            for (const auto &[neighbour_node_id, weight] : graph.getAdjList().at(visiting_node))
            {
                (void)weight; // no se usan pesos en BFS
                if (!seen[neighbour_node_id])
                {
                    seen[neighbour_node_id] = true;
                    result.parent[neighbour_node_id] = visiting_node;
                    result.depth[neighbour_node_id] = result.depth[visiting_node] + 1;
                    fifo_queue.push(neighbour_node_id);
                }
            }
        }
        return result;
    }

    // ---------- DFS (iterativa para evitar stack profundo) ----------

    template <typename Weight = double>
    TraversalResult DFS(const AdjacencyListGraph<Weight> &g, int source)
    {
        TraversalResult r;
        r.source = source;
        std::unordered_map<int, bool> seen;
        for (const auto &[u, _] : g.getAdjList())
        {
            r.parent[u] = -1;
            r.depth[u] = std::numeric_limits<int>::max();
        }
        if (!g.getAdjList().count(source))
            return r;

        std::stack<std::pair<int, int>> st; // (nodo, depth)
        st.push({source, 0});
        while (!st.empty())
        {
            auto [u, d] = st.top();
            st.pop();
            if (seen[u])
                continue;
            seen[u] = true;
            r.order.push_back(u);
            r.depth[u] = d;

            // para obtener un orden similar al recursivo, empujamos vecinos en orden inverso
            const auto &nbrs = g.getAdjList().at(u);
            for (auto it = nbrs.rbegin(); it != nbrs.rend(); ++it)
            {
                int v = it->first;
                if (!seen[v])
                {
                    if (r.parent[v] == -1)
                        r.parent[v] = u;
                    st.push({v, d + 1});
                }
            }
        }
        return r;
    }

    // ---------- Dijkstra ----------

    template <typename Weight = double>
    DijkstraResult<Weight> Dijkstra(const AdjacencyListGraph<Weight> &g, int source)
    {
        DijkstraResult<Weight> r;
        r.source = source;

        struct QItem
        {
            int node;
            Weight dist;
            bool operator>(const QItem &other) const { return dist > other.dist; }
        };

        // init
        std::cout << "Inicializando nodos...\n";
        for (const auto& [node, _] : g.getAdjList())
        {

            r.dist[node] = std::numeric_limits<Weight>::max();
            r.parent[node] = -1;
            std::cout << "Nodo " << node 
              << ": dist = " << r.dist[node] 
              << ", parent = " << r.parent[node] << "\n";
        }

        if (!g.getAdjList().count(source))
        {
            std::cout << "El nodo fuente " << source << " no está en el grafo.\n";
            return r;
        }

        r.dist[source] = static_cast<Weight>(0);
        std::cout << "Nodo fuente " << source << ": dist = 0\n";

        std::priority_queue<QItem, std::vector<QItem>, std::greater<QItem>> pq;
        pq.push({source, r.dist[source]});

        while (!pq.empty())
        {
            auto [u, du] = pq.top();
            pq.pop();
            std::cout << "Procesando nodo " << u << " con dist=" << du << "\n";

            if (du != r.dist[u])
            {
                std::cout << "Entrada obsoleta, saltando\n";
                continue; // entrada obsoleta
            }

            for (const auto &[v, w] : g.getAdjList().at(u))
            {
                std::cout << "  Arista " << u << " -> " << v << " peso=" << w << "\n";

                if (w < static_cast<Weight>(0))
                {
                    std::cout << "  Peso negativo, ignorando\n";
                    continue;
                }

                Weight cand = r.dist[u] + w;
                std::cout << "  dist[" << u << "] + w = " << r.dist[u] << " + " << w
                        << " = " << cand << ", dist[" << v << "] = " << r.dist[v] << "\n";

                if (cand < r.dist[v])
                {
                    std::cout << "  Actualizando dist[" << v << "] de " << r.dist[v]
                            << " a " << cand << ", parent[" << v << "] = " << u << "\n";
                    r.dist[v] = cand;
                    r.parent[v] = u;
                    pq.push({v, cand});
                }
            }
        }

        std::cout << "Dijkstra finalizado.\n";
        for (const auto& [node, dist] : r.dist)
            std::cout << "Nodo " << node << ": dist=" << dist << ", parent=" << r.parent[node] << "\n";

        return r;
    }

    // ---------- reconstrucción de camino (opcional de ayuda) ----------

    template <typename Weight = double>
    std::vector<int> ReconstructPath(int target, const std::unordered_map<int, int> &parent)
    {
        std::vector<int> path;
        if (!parent.count(target))
            return path;
        int cur = target;
        while (cur != -1)
        {
            path.push_back(cur);
            auto it = parent.find(cur);
            if (it == parent.end())
                break;
            cur = it->second;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
} // namespace Algorithms
