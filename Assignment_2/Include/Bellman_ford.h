#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "csr.h"

#define INF 2147483647

/*
 * Returns:
 * 0 -> no negative cycle reachable from source
 * 1 -> negative cycle detected
 */
int bellman_ford(
    const CSRGraph *graph,
    int source,
    long long *distance
);

#endif