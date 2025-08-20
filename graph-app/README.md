# 📊 Graph Algorithms App

Este proyecto es una aplicación en **C++20** para experimentar con **grafos** y algoritmos clásicos como **Dijkstra**.  
Incluye una API HTTP (con [Crow](https://github.com/CrowCpp/Crow)) para crear grafos, consultarlos y ejecutar algoritmos sobre ellos.

---

## ⚡️ Características

- Representación de grafos mediante **lista de adyacencia** (`AdjacencyListGraph`).
- Soporte para grafos **dirigidos** y **no dirigidos**.
- Algoritmo de **Dijkstra** para caminos más cortos.
- API REST con endpoints como:
  - `POST /add_graph`
  - `POST /run_algorithm`
  - `GET /get_graph/<id>`
---

## 🔧 Requisitos

- [CMake](https://cmake.org/) (>= 3.15)
- [Conan](https://conan.io/) (>= 2.x)
- Compilador con soporte **C++20**  
  (ej. Visual Studio 2022 en Windows, gcc/clang en Linux/MacOS)

---

## ⚙️ Configuración del proyecto

El proyecto incluye un script `setup_projects.sh` para configurar y compilar automáticamente el entorno.  

### 1. Preparar el entorno
Instala dependencias y configura Conan:

```bash
./setup_projects.sh
```

Por defecto compila en modo release.
Si quieres compilar en debug:

```bash
./setup_projects.sh debug
```