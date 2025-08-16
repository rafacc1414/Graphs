# 📄 GraphGenerator.hpp

Este módulo implementa utilidades para la **generación aleatoria de grafos ponderados**, tanto en **lista de adyacencia** como en **matriz de adyacencia**, con soporte para **grafos dirigidos y no dirigidos**.

---

## ✨ Función auxiliar: randomWeight

### Descripción
Genera un peso aleatorio dentro de un rango definido por valores mínimo y máximo.  
El comportamiento depende del tipo de dato:

- Para valores enteros se utiliza una distribución uniforme discreta.  
- Para valores reales (como float o double) se utiliza una distribución uniforme continua.  

### Teoría
En los grafos ponderados, los pesos de las aristas suelen representar un coste, distancia o capacidad. Al utilizar distribuciones uniformes, todos los valores posibles dentro del rango tienen la misma probabilidad de ser seleccionados, garantizando neutralidad en la asignación de pesos.

---

## 🏗️ Clase: GraphGenerator

### Método: generateAdjacencyListGraph

#### Parámetros
- Número de nodos.  
- Probabilidad de arista entre dos nodos.  
- Peso mínimo y máximo.  
- Indicador de si el grafo es dirigido o no.  

#### Retorno
Un grafo representado mediante lista de adyacencia con aristas y pesos generados aleatoriamente.

#### Teoría
Este método utiliza el modelo de **Erdős–Rényi (G(n,p))**, donde cada par de nodos tiene una probabilidad determinada de estar conectado.  
Si el grafo es no dirigido, se evita la duplicación de aristas al considerar únicamente pares de nodos distintos con un índice mayor. Los pesos se asignan mediante la función auxiliar randomWeight.

---

### Método: generateAdjacencyMatrixGraph

#### Parámetros
Los mismos que en la versión basada en lista de adyacencia.  

#### Retorno
Un grafo representado mediante matriz de adyacencia de tamaño n x n, en la cual cada celda indica la existencia y el peso de una arista.  

#### Teoría
Este enfoque es más costoso en memoria ya que requiere O(n²), pero proporciona acceso inmediato a la existencia de aristas entre dos nodos. Es más adecuado para grafos densos, donde la mayoría de pares de nodos están conectados.

---

## 📊 Comparativa de representaciones

- **Lista de adyacencia**: requiere memoria proporcional a la suma de nodos y aristas, y resulta más eficiente en grafos dispersos.  
- **Matriz de adyacencia**: requiere memoria cuadrática con respecto al número de nodos, pero permite acceso inmediato a la existencia de aristas. Es más útil en grafos densos.  

---

## 📚 Referencias

- Modelo Erdős–Rényi (G(n,p))  
- Distribución uniforme discreta (`uniform_int_distribution`)  
- Distribución uniforme continua (`uniform_real_distribution`)  


# Algoritmos de Grafos

Este módulo implementa tres algoritmos fundamentales de grafos:  
- **BFS (Breadth-First Search)**  
- **DFS (Depth-First Search)**  
- **Dijkstra’s Algorithm**  

Todos los algoritmos devuelven resultados en estructuras que pueden ser serializadas a **JSON**, lo que facilita su integración en APIs y aplicaciones.

---

## 1. Breadth-First Search (BFS)

### Teoría
El algoritmo **BFS (Búsqueda en Anchura)** recorre el grafo partiendo de un nodo inicial y visitando primero todos los nodos de distancia 1, luego los de distancia 2, y así sucesivamente.  
Esto se consigue usando una **cola (FIFO)**, lo que garantiza que los nodos se procesen en orden de cercanía.

### Pasos principales
1. Inicializar todos los nodos como **no visitados**.  
2. Poner el nodo inicial en la cola.  
3. Mientras la cola no esté vacía:  
   - Sacar un nodo de la cola.  
   - Visitarlo y marcarlo como procesado.  
   - Insertar en la cola todos sus vecinos no visitados.  

### Complejidad
- **Tiempo:** `O(V + E)` donde `V` es el número de nodos y `E` el número de aristas.  
- **Espacio:** `O(V)` debido a la cola y a las estructuras de visitados.  

### Resultados devueltos
- **order:** lista de nodos visitados en orden BFS.  
- **parent:** quién descubrió a cada nodo (útil para reconstruir caminos).  
- **depth:** distancia en número de aristas desde el nodo inicial.  

---

## 2. Depth-First Search (DFS)

### Teoría
El algoritmo **DFS (Búsqueda en Profundidad)** explora el grafo intentando avanzar lo más lejos posible en una rama antes de retroceder.  
Esto se puede implementar con **recursión** o con una **pila explícita (LIFO)**.

### Pasos principales
1. Inicializar todos los nodos como **no visitados**.  
2. Comenzar desde un nodo inicial.  
3. Explorar recursivamente cada vecino no visitado antes de volver atrás.  

### Propiedades importantes
- Genera un **árbol DFS** que refleja la estructura de descubrimiento de nodos.  
- Permite detectar **ciclos**, **componentes conexas** y realizar ordenaciones topológicas en grafos dirigidos acíclicos.  

### Complejidad
- **Tiempo:** `O(V + E)`  
- **Espacio:** `O(V)` por la pila de recursión o una pila explícita.  

### Resultados devueltos
- **order:** lista de nodos en orden de visita DFS.  
- **parent:** nodo desde el que se descubrió cada vértice.  
- **depth:** profundidad alcanzada en el árbol DFS.  

---

## 3. Dijkstra’s Algorithm

### Teoría
El **algoritmo de Dijkstra** encuentra la distancia más corta desde un nodo inicial hasta todos los demás en un grafo ponderado con **pesos no negativos**.  
Se basa en la técnica de **relajación**: actualizar iterativamente las distancias mínimas conocidas.

### Pasos principales
1. Inicializar todas las distancias en infinito (`∞`), salvo la del nodo inicial en `0`.  
2. Usar una **cola de prioridad (min-heap)** para seleccionar el nodo con menor distancia conocida.  
3. Para cada vecino del nodo extraído, comprobar si se mejora la distancia (`relajación`).  
4. Repetir hasta procesar todos los nodos alcanzables.  

### Propiedades importantes
- Garantiza encontrar el camino más corto en grafos sin pesos negativos.  
- Permite reconstruir caminos mediante la estructura `parent`.  

### Complejidad
- **Tiempo:** `O((V + E) log V)` usando `std::priority_queue`.  
- **Espacio:** `O(V)` para almacenar distancias y predecesores.  

### Resultados devueltos
- **dist:** distancia mínima desde el origen a cada nodo.  
- **parent:** nodo previo en el camino más corto para reconstruir trayectorias.  

---

## 4. Reconstrucción de Caminos

Con la información de `parent` se pueden reconstruir los caminos:  
1. Empezar desde el nodo destino.  
2. Seguir los punteros `parent` hasta llegar al origen.  
3. Invertir la secuencia para obtener el camino en orden correcto.  

Esto funciona tanto para BFS, DFS como Dijkstra.

---
