#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <limits.h>

#define FW_INF LLONG_MAX

/*
 * Returns:
 * 0 -> no negative cycle
 * 1 -> negative cycle detected
 */
int floyd_warshall(
    int V,
    long long **dist
);

#endif