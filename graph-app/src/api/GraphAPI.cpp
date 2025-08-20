#include "api/GraphAPI.hpp"
#include "graph_repository/GraphRepository.hpp"
#include "graph_core/GraphGenerator.hpp"
#include "graph_core/Algorithms.hpp"

static GraphRepository repository;

void GraphAPI::registerEndpoints(crow::SimpleApp& app) {
    // Endpoint: /generate_graph
    CROW_ROUTE(app, "/generate_graph").methods("POST"_method)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400);

        // Extraer parámetros
        size_t nodeCount = body["node_count"].i();
        double edgeProb  = body["edge_probability"].d();
        bool directed    = body["directed"].b();

        // Crear grafo
        auto graph = GraphGenerator::generateAdjacencyListGraph<int>(
            nodeCount, edgeProb, 1, 10, directed
        );

        // Guardar en repositorio
        int id = repository.addGraph(std::move(graph));

        crow::json::wvalue res;
        res["graph_id"] = id;
        return crow::response(res);
    });

    // Endpoint: /run_algorithm
    CROW_ROUTE(app, "/run_algorithm").methods("POST"_method)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400);

        int graphId     = body["graph_id"].i();
        std::string alg = body["algorithm"].s();
        int start       = body["start_node"].i();

        auto& graph = repository.getGraph<AdjacencyListGraph<int>>(graphId);

        nlohmann::json result_json;
        if (alg == "bfs") {
            TraversalResult result = Algorithms::BFS(graph, start);
            result_json = GraphAPI::serialize(result);
        } else if (alg == "dfs") {
            TraversalResult result = Algorithms::DFS(graph, start);
            result_json = GraphAPI::serialize(result);
        } else if (alg == "dijkstra") {
            DijkstraResult result = Algorithms::Dijkstra(graph, start);
            result_json = GraphAPI::serialize(result);
        } else {
            return crow::response(400, "Unknown algorithm");
        }

        crow::json::wvalue res = crow::json::load(result_json.dump());

        return crow::response(res);
    });

    // Endpoint: /get_graph/<graph_id>
    CROW_ROUTE(app, "/get_graph/<int>").methods("GET"_method)
    ([](int graphId){
        try {
            auto& graph = repository.getGraph<AdjacencyListGraph<int>>(graphId);

            nlohmann::json result = GraphAPI::serialize<int>(graph);

            crow::json::wvalue res = crow::json::load(result.dump());
            
            return crow::response(res);
        } catch (const std::exception& e) {
            return crow::response(404, "Graph not found");
        }
    });

}
