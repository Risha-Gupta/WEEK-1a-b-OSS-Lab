# Dijkstra-C — Code Structure & Function Documentation

**Original project:** `maximetinu/Dijkstra-C` (GitHub).  
**Source:** https://github.com/maximetinu/Dijkstra-C. :contentReference[oaicite:1]{index=1}

This document is a reverse-engineering and developer-friendly documentation of the Dijkstra-C project. It explains the repository layout, the role of each file/module, and a per-function description (purpose, inputs, outputs, and important details). Use this documentation to understand, extend, or grade the project.

---

## 1. Project overview

Dijkstra-C is a C implementation of Dijkstra’s single-source shortest-path algorithm. The project separates algorithm logic from IO and optional graph drawing facilities. It supports reading the graph from CSV files or from terminal input and can output results to the terminal or to files. The project also includes utilities to produce a Graphviz-compatible output for visualization. :contentReference[oaicite:2]{index=2}

---

## 2. Repository structure (high-level)


> Note: file/identifier names above are based on the upstream layout and public interface described by the project. See the upstream repository for the exact filenames and the 3 public interfaces. :contentReference[oaicite:3]{index=3}

---

## 3. Design & separation of concerns

The project follows a clean separation of concerns:

- `dijkstra.*` — **Algorithm core**: contains the implementation of Dijkstra's algorithm and any data structures required (graph representation, distance arrays, predecessor arrays, helper functions).
- `IO_dijkstra.*` — **Input/Output utilities**: parsing CSV adjacency files or reading adjacency matrices from stdin, parsing command-line arguments, formatting/writing output files or terminal output.
- `graph_drawer.*` — **(Optional) Graph visualization**: prepares a Graphviz DOT description and calls `dot` to render the shortest path graph image (optional dependency: Graphviz).

This separation makes the algorithm reusable: `dijkstra.h` exposes the computation functions only, without coupling to IO or rendering code. :contentReference[oaicite:4]{index=4}

---

## 4. Data structures (typical / observed)

The project uses an adjacency matrix or adjacency list representation depending on the input format. Typical internal structures include:

- `int n` — number of vertices.
- `int **adj_matrix` or `int adj_matrix[MAX][MAX]` — adjacency matrix of weights (use `INFTY` for no-edge).
- `int *visited` — boolean/flag array marking processed nodes.
- `double *dist` (or `int *dist`) — current shortest distance estimates from the source.
- `int *prev` — predecessor array to reconstruct shortest path.

---

## 5. Function-level documentation

> Below are concise, implementation-agnostic descriptions of the main functions you will find (or should find) in the repository. Names in your local copy might vary slightly — map by purpose if names differ.

### 5.1 `dijkstra.h / dijkstra.c` — core algorithm

**`void dijkstra(int n, const int adj_matrix[n][n], int source, double dist[], int prev[])`**  
- **Purpose:** Compute shortest path distances from `source` to all nodes using Dijkstra's algorithm.  
- **Inputs:**  
  - `n` — number of vertices.  
  - `adj_matrix` — `n x n` adjacency matrix, with some sentinel (e.g., a large number or `INFINITY`) for absent edges.  
  - `source` — index (0-based or 1-based depending on project) of source vertex.  
- **Outputs:**  
  - `dist[]` — array (length `n`) filled with shortest distances from `source`. If a node is unreachable, its distance remains `INFINITY`.  
  - `prev[]` — predecessor array for path reconstruction; `prev[v]` is the previous node on shortest path from `source` to `v`, or `-1`/`NULL` if none.  
- **Behavior / Notes:**  
  - The algorithm typically uses an O(n^2) method (min over unvisited nodes) if adjacency matrix is used. Some implementations may use a priority queue for O(E log V), but the upstream project focuses on clarity and matrix-based input.  
  - Must not assume negative weights — Dijkstra’s algorithm requires non-negative edge weights.  
  - Handles directed or undirected graphs depending on how adjacency is filled.

**`static int min_distance_index(const double dist[], const int visited[], int n)`**  
- **Purpose:** Helper to return the index of the unvisited node with smallest `dist[]`.  
- **Inputs:** `dist[]`, `visited[]`, `n`.  
- **Output:** index `u` of chosen node, or `-1` if none left.  
- **Edge cases:** If all remaining unvisited nodes have `INFINITY`, return `-1` (algorithm finishes).

**`void reconstruct_path(int target, const int prev[], int path[], int *path_len)`**  
- **Purpose:** Rebuilds the shortest path from `source` to `target` by following `prev[]` backwards then reversing.  
- **Inputs:** `target`, `prev[]`.  
- **Outputs:** `path[]` populated with vertex indices in order (source → ... → target), `path_len` set to length.  
- **Notes:** Caller must provide enough space for `path[]` (size `n`).

---

### 5.2 `IO_dijkstra.h / IO_dijkstra.c` — input & output

**`int read_adjacency_matrix_from_csv(const char *filename, int ***out_matrix, int *out_n)`**  
- **Purpose:** Read a CSV adjacency matrix file. Each CSV row corresponds to one row of adjacency weights.  
- **Inputs:** `filename` (path to CSV).  
- **Outputs:** Dynamically allocated `out_matrix` (`n x n`) and `out_n` set to `n`.  
- **Return:** 0 on success, non-zero on failure.  
- **Notes:** Malformed CSV should produce an error; missing values or non-numeric cells must be handled gracefully.

**`int read_adjacency_from_stdin(int ***out_matrix, int *out_n)`**  
- **Purpose:** Interactive read of `n` and then `n x n` adjacency values from terminal. Useful when not using files.

**`int parse_commandline_args(int argc, char *argv[], char **infile, char **outfile, int *start, int *target, int *verbose_flag)`**  
- **Purpose:** Command-line argument parser that supports multiple modes: terminal IO, file IO, non-verbose batch mode.  
- **Behavior:** Recognizes usages like:  
