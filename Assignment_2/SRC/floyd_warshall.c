#include "../Include/floyd_warshall.h"

int floyd_warshall(
    int V,
    long long **dist
)
{
    /*
     * k = intermediate vertex
     */
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            /*
             * No path from i to k.
             */
            if (dist[i][k] == FW_INF)
            {
                continue;
            }

            for (int j = 0; j < V; j++)
            {
                /*
                 * No path from k to j.
                 */
                if (dist[k][j] == FW_INF)
                {
                    continue;
                }

                long long new_distance =
                    dist[i][k] + dist[k][j];

                if (new_distance < dist[i][j])
                {
                    dist[i][j] = new_distance;
                }
            }
        }
    }

    /*
     * Negative cycle detection.
     *
     * If dist[i][i] < 0, vertex i belongs to
     * or can reach a negative-weight cycle.
     */
    for (int i = 0; i < V; i++)
    {
        if (dist[i][i] < 0)
        {
            return 1;
        }
    }

    return 0;
}