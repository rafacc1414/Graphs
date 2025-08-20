# REST API para Generación de Grafos y Algoritmos

En esta etapa se implementa una **API REST mínima** con dos endpoints principales:  

- `/generate_graph` → Para crear un grafo con parámetros configurables.  
- `/run_algorithm` → Para ejecutar un algoritmo sobre un grafo generado.  

Esto permite que otros programas (por ejemplo, una interfaz web o un cliente externo) interactúen con el motor de grafos de forma sencilla.

---

## 1. Arquitectura General

La API expone un **servidor web ligero** que recibe peticiones en formato JSON y devuelve las respuestas también en JSON.  

El flujo básico es:  
1. El cliente pide un grafo con `/generate_graph`.  
2. El cliente recibe un identificador único del grafo.  
3. El cliente ejecuta un algoritmo sobre ese grafo mediante `/run_algorithm`.  

Esto desacopla la **definición del grafo** de la **ejecución de algoritmos**.

---

## 2. Endpoint `/generate_graph`

### Descripción
Crea un grafo nuevo en memoria.  
El grafo puede ser representado como lista de adyacencia o como matriz de adyacencia.

### Parámetros de entrada (JSON)
- `type`: `"adjacency_list"` o `"adjacency_matrix"`  
- `node_count`: número de nodos  
- `edge_probability`: probabilidad de arista entre nodos  
- `min_weight`: peso mínimo de aristas  
- `max_weight`: peso máximo de aristas  
- `directed`: `true` o `false`  

### Respuesta (JSON)
- `graph_id`: identificador único del grafo generado  
- `summary`: información básica (número de nodos, número de aristas, dirigido/no dirigido)

---

## 3. Endpoint `/run_algorithm`

### Descripción
Ejecuta un algoritmo sobre un grafo previamente generado.

### Parámetros de entrada (JSON)
- `graph_id`: identificador del grafo  
- `algorithm`: `"bfs"`, `"dfs"` o `"dijkstra"`  
- `start_node`: nodo de inicio (requerido para BFS, DFS, Dijkstra)  

### Respuesta (JSON)
Dependiendo del algoritmo:
- Para **BFS/DFS**: orden de visita, padres, profundidades.  
- Para **Dijkstra**: distancias mínimas y padres para reconstrucción de caminos.

---

## 4. Ejemplo de Flujo Completo

1. El cliente llama a `/generate_graph` con parámetros para crear un grafo.  
2. Recibe un `graph_id` como respuesta.  
3. Llama a `/run_algorithm` pasando el `graph_id` y `"bfs"`.  
4. Obtiene en la respuesta la estructura del recorrido BFS.  

---

## 5. Complejidad y Eficiencia

- El **tiempo de respuesta** dependerá del tamaño del grafo y el algoritmo elegido.  
- La **serialización JSON** se diseña para ser ligera pero informativa.  
- Los grafos se almacenan en memoria durante la vida del servidor, por lo que se recomienda añadir más adelante:  
  - Persistencia en base de datos.  
  - Cacheo de resultados de algoritmos ya ejecutados.  

---

## 6. Próximos Pasos

Una vez creada esta API mínima, se puede:  
- Desplegar en un servidor web o en contenedores Docker.  
- Conectarla con una interfaz web para visualización de grafos.  
- Extenderla con más algoritmos de grafos (MST, Floyd-Warshall, A*).  
