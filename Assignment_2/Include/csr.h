#ifndef CSR_H
#define CSR_H

typedef struct
{
    int V;
    int E;

    int *row_ptr;
    int *col_idx;
    int *values;

} CSRGraph;

/*
 * Convert adjacency-list data into CSR.
 *
 * adjacency:
 * adjacency[u] contains:
 * [neighbor, weight, neighbor, weight, ...]
 *
 * degree[u] = number of outgoing edges from u
 */
CSRGraph *create_csr(
    int V,
    int E,
    int **adjacency,
    int *degree
);

void free_csr(CSRGraph *graph);

#endif