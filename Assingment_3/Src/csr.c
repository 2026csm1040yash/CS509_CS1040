#include <stdlib.h>
#include "../Include/csr.h"

CSRGraph *create_csr(int v, int E, int **adjacency, int *deg)
{
    CSRGraph *graph = malloc(sizeof(CSRGraph));
    if (graph == NULL) return NULL;

    graph->v = v;
    graph->E = E;
    graph->row_ptr = malloc((size_t)(v + 1) * sizeof(int));

    if (graph->row_ptr == NULL) {
        free(graph);
        return NULL;
    }

    graph->row_ptr[0] = 0;
    for (int i = 0; i < v; ++i)
        graph->row_ptr[i + 1] = graph->row_ptr[i] + deg[i];

    int total = graph->row_ptr[v];
    graph->col_idx = total > 0 ? malloc((size_t)total * sizeof(int)) : NULL;
    graph->values = total > 0 ? malloc((size_t)total * sizeof(int)) : NULL;

    if (total > 0 && (graph->col_idx == NULL || graph->values == NULL)) {
        free(graph->row_ptr);
        free(graph->col_idx);
        free(graph->values);
        free(graph);
        return NULL;
    }

    int k = 0;
    for (int u = 0; u < v; ++u) {
        for (int j = 0; j < deg[u]; ++j) {
            graph->col_idx[k] = adjacency[u][2 * j];
            graph->values[k] = adjacency[u][2 * j + 1];
            ++k;
        }
    }

    return graph;
}

void free_csr(CSRGraph *graph)
{
    if (graph == NULL) return;
    free(graph->row_ptr);
    free(graph->col_idx);
    free(graph->values);
    free(graph);
}
