#include <stdio.h>
#include <stdlib.h>

#include "../Include/csr.h"

CSRGraph *create_csr(
    int V,
    int E,
    int **adjacency,
    int *degree
)
{
    CSRGraph *graph = malloc(sizeof(CSRGraph));

    if (graph == NULL)
    {
        return NULL;
    }

    graph->V = V;
    graph->E = E;

    graph->row_ptr = malloc((V + 1) * sizeof(int));
    graph->col_idx = malloc(E * sizeof(int));
    graph->values = malloc(E * sizeof(int));

    if (graph->row_ptr == NULL ||
        graph->col_idx == NULL ||
        graph->values == NULL)
    {
        free(graph->row_ptr);
        free(graph->col_idx);
        free(graph->values);
        free(graph);

        return NULL;
    }

    graph->row_ptr[0] = 0;

    for (int i = 0; i < V; i++)
    {
        graph->row_ptr[i + 1] =
            graph->row_ptr[i] + degree[i];
    }

    int index = 0;

    for (int u = 0; u < V; u++)
    {
        for (int j = 0; j < degree[u]; j++)
        {
            graph->col_idx[index] =
                adjacency[u][2 * j];

            graph->values[index] =
                adjacency[u][2 * j + 1];

            index++;
        }
    }

    return graph;
}

void free_csr(CSRGraph *graph)
{
    if (graph == NULL)
    {
        return;
    }

    free(graph->row_ptr);
    free(graph->col_idx);
    free(graph->values);

    free(graph);
}