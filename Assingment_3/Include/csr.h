#ifndef CSR_H
#define CSR_H

typedef struct {
    int v;
    int E;
    int *row_ptr;
    int *col_idx;
    int *values;
} CSRGraph;

CSRGraph *create_csr(int vertices, int edges, int **adjacency, int *degree);
void free_csr(CSRGraph *graph);

#endif
