# Función para Generar Grafos Aleatorios

Esta función permite generar grafos aleatorios basados en varios parámetros, tales como:

- Número de nodos
- Probabilidad de existencia de una arista entre dos nodos
- Rango de pesos de las aristas
- Si el grafo es dirigido o no

---

## Objetivo

El propósito de la función es:

- **Testing:** Probar algoritmos de grafos en diferentes tamaños y densidades.  
- **Benchmarking:** Medir rendimiento con grafos grandes o densos.  
- **Simulación:** Modelar redes, caminos y otras estructuras aleatorias.

---

## Lógica Paso a Paso

1. **Crear el grafo vacío**  
   Según el tipo (`AdjacencyListGraph` o `AdjacencyMatrixGraph`) y con el número de nodos indicado.

2. **Recorrer pares de nodos**  
   - Para grafos no dirigidos, evitar duplicar aristas (`A→B` y `B→A`).  
   - Para grafos dirigidos, considerar ambas direcciones si la probabilidad lo permite.

3. **Decidir si añadir una arista**  
   - Generar un número aleatorio entre `[0, 1]`.  
   - Si el número es menor que `edgeProbability`, se añade la arista.

4. **Asignar peso aleatorio**  
   - Elegir un valor entre `minWeight` y `maxWeight`.

5. **Devolver el grafo generado**  
   - Contendrá todos los nodos y aristas según los parámetros especificados.

---

## Ejemplo de Uso

```cpp
auto g = GraphGenerator::generateRandomGraph<double>(
    5,        // 5 nodos
    0.4,      // 40% de probabilidad de arista
    1.0, 10.0,// pesos entre 1 y 10
    false     // no dirigido
);
