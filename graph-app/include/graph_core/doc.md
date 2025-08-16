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
