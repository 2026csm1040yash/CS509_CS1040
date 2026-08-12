# CS509 Assignment 2

## Algorithms

### Individual Task

- Bellman-Ford
- Floyd-Warshall

## Shortest Path Algorithms

### Bellman-Ford

Bellman-Ford calculates the shortest distance from a single source vertex
to every reachable vertex.

The algorithm supports negative edge weights and detects negative-weight
cycles reachable from the source.

- Time Complexity: **O(V × E)**
- Graph Type: **Directed**
- Input Representation: **CSR**

### Floyd-Warshall

Floyd-Warshall calculates the shortest distance between every pair of
vertices.

The algorithm uses dynamic programming and supports negative edge
weights as long as there is no negative-weight cycle.

- Time Complexity: **O(V³)**
- Space Complexity: **O(V²)**
- Graph Representation: **Adjacency Matrix**

---

# CSR Graph Representation

The Bellman-Ford implementation uses **Compressed Sparse Row (CSR)**
representation.

The CSR structure contains:

- `row_ptr`
- `col_idx`
- `values`

The adjacency-list input is converted to CSR before the algorithm
execution.

CSR conversion time is **not included** in the algorithm execution time.

---

# Timing

Only the algorithm execution time is measured.

The following operations are **NOT** included:

- File reading
- Input parsing
- Memory allocation during setup
- CSR conversion
- Matrix construction
- Output generation
- Output file writing

Timing begins immediately before calling the algorithm and stops
immediately after the algorithm completes.

---

# Test Cases

## Bellman-Ford

The following graph sizes are used:

- 10 vertices
- 100 vertices
- 10,000 vertices
- 50,000 vertices
- 100,000 vertices

## Floyd-Warshall

The following graph sizes are used:

- 10 vertices
- 100 vertices
- 500 vertices
- 1,000 vertices
- 2,000 vertices

Additional test cases are included for negative-cycle detection.

---

# Bellman-Ford Results

| Test Cases | Vertices | Edges | Source | Time | Status |
| --------------------------------: | --------: | ----: | -----: | ----: | :----: |
| bf_10.txt | 10 | 22 | 0 | ___ ms | Pass |
| bf_100.txt | 100 | 292 | 0 | ___ ms | Pass |
| bf_10000.txt | 10,000 | 39,916 | 0 | ___ ms | Pass |
| bf_50000.txt | 50,000 | 199,723 | 0 | ___ ms | Pass |
| bf_100000.txt | 100,000 | 399,480 | 0 | ___ ms | Pass |

---

# Floyd-Warshall Results

| Test Cases | Vertices | Time | Status |
| --------------------------------: | --------: | ----: | :----: |
| fw_10.txt | 10 | ___ ms | Pass |
| fw_100.txt | 100 | ___ ms | Pass |
| fw_500.txt | 500 | ___ ms | Pass |
| fw_1000.txt | 1,000 | ___ ms | Pass |
| fw_2000.txt | 2,000 | ___ ms | Pass |

---

# Negative Cycle Detection

### Bellman-Ford

The algorithm performs an additional relaxation pass after the
`V - 1` iterations.

If an edge can still be relaxed, a negative-weight cycle reachable
from the source is detected.

Test case:

```text
bf_negative_cycle.txt
```
# Observations

- Bellman-Ford supports negative edge weights and detects reachable negative-weight cycles.
- Floyd-Warshall calculates the shortest paths between all pairs of vertices.
- Bellman-Ford uses **CSR representation** for efficient graph processing.
- Floyd-Warshall uses a **distance matrix** for all-pairs shortest-path computation.
- Bellman-Ford has a time complexity of **O(V × E)**.
- Floyd-Warshall has a time complexity of **O(V³)**.
- Bellman-Ford is more suitable for sparse graphs, especially for larger graph sizes.
- Floyd-Warshall requires significantly more computation as the number of vertices increases.
- The 10-vertex and 100-vertex test cases are used to cross-check Bellman-Ford results with the corresponding rows of the Floyd-Warshall distance matrix.
- The results of both algorithms are expected to match for the common test cases.
- Negative-cycle test cases verify that both algorithms correctly identify negative-weight cycles.