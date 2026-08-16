# CS509 Assignment 3 — Individual Task

## Algorithms

- Kruskal's Minimum Spanning Tree (MST)
- Prim's Minimum Spanning Tree (MST)
- CSR graph representation
- Disjoint Set Union (DSU) for Kruskal
- Binary min-heap for Prim

## Language

The project is implemented entirely in **C** using `.c` source files and standard C libraries.

## Structure

```text
Assignment_3/
├── Driver/
│   └── main.c
├── Include/
│   ├── csr.h
│   └── mst.h
├── Src/
│   ├── csr.c
│   └── mst.c
├── Testcases/
│   └── MST/
│       ├── mst_10.txt
│       ├── mst_100.txt
│       ├── mst_10000.txt
│       ├── mst_50000.txt
│       └── mst_100000.txt
├── Output/
├── Makefile
└── README.md
```

## Input Format

Each test case begins with:

```text
V E
```

followed by `V` adjacency-list lines. Each line contains the vertex ID, its degree, and `degree` pairs of neighbour and edge weight.

The graph is a weighted undirected graph. Each undirected edge is represented in both endpoint adjacency lists, while `E` counts each undirected edge once.

## CSR Representation

The input adjacency list is converted into:

- `row_ptr`
- `col_idx`
- `values`

CSR construction is preprocessing and is excluded from the measured algorithm execution time.

## Kruskal

Kruskal sorts the undirected edges by weight and uses DSU/Union-Find to avoid cycles.

Time complexity: **O(E log E)**.

## Prim

Prim starts from vertex `0` and uses a binary min-heap to repeatedly select the minimum-weight edge that expands the current tree.

Time complexity: **O(E log V)** with the binary heap implementation.

## Timing

Only the algorithm execution is timed. Input reading, adjacency-list construction, CSR conversion, and output printing are outside the timed region.

## Compilation

Using GCC:

```bash
gcc -Wall -Wextra -O2 Driver/main.c Src/mst.c Src/csr.c -IInclude -o assignment3
```

Using Make:

```bash
make
```

## Execution

Kruskal:

```bash
./assignment3 kruskal Testcases/MST/mst_10.txt
```

Windows PowerShell:

```powershell
.\assignment3.exe kruskal .\Testcases\MST\mst_10.txt
```

Prim:

```bash
./assignment3 prim Testcases/MST/mst_10.txt
```

Windows PowerShell:

```powershell
.\assignment3.exe prim .\Testcases\MST\mst_10.txt
```

## Required Graph Sizes

- 10 vertices
- 100 vertices
- 10,000 vertices
- 50,000 vertices
- 100,000 vertices

## Correctness Check

Kruskal and Prim should produce the same total MST weight for every connected test graph.

## Output

The driver prints only the MST result and measured algorithm execution time to the terminal.
The same output is also stored in the `Output/` directory.

Example terminal output:

```text
MST total weight: 152
MST edges: 9
Connected graph: true
Execution time: 0.004000 ms
```

For an input file `mst_10.txt`, the generated files are:

- `Output/kruskal_mst_10.txt`
- `Output/prim_mst_10.txt`

File writing and result printing are outside the timed algorithm region.
