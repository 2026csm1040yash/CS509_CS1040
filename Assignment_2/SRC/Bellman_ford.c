#include <limits.h>

#include "../Include/Bellman_ford.h"

int bellman_ford(
    const CSRGraph *graph,
    int source,
    long long *dist
)
{
    int V = graph->V;

    /*
     * Initialization
     */
    for (int i = 0; i < V; i++)
    {
        dist[i] = LLONG_MAX;
    }

    dist[source] = 0;

    /*
     * Relax all edges V-1 times.
     */
    for (int pass = 0; pass < V - 1; pass++)
    {
        int changed = 0;

        for (int u = 0; u < V; u++)
        {
            if (dist[u] == LLONG_MAX)
            {
                continue;
            }

            for (int index = graph->row_ptr[u];
                 index < graph->row_ptr[u + 1];
                 index++)
            {
                int v = graph->col_idx[index];
                int weight = graph->values[index];

                if (dist[u] + weight < dist[v])
                {
                    dist[v] =
                        dist[u] + weight;

                    changed = 1;
                }
            }
        }

        /*
         * Early termination.
         *
         * If no dist changed during a complete
         * pass, the shortest paths are already final.
         */
        if (!changed)
        {
            break;
        }
    }

    /*
     * Extra pass for negative-cycle detection.
     */
    for (int u = 0; u < V; u++)
    {
        if (dist[u] == LLONG_MAX)
        {
            continue;
        }

        for (int index = graph->row_ptr[u];
             index < graph->row_ptr[u + 1];
             index++)
        {
            int v = graph->col_idx[index];
            int weight = graph->values[index];

            if (dist[u] + weight < dist[v])
            {
                return 1;
            }
        }
    }

    return 0;
}