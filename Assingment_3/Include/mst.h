#ifndef MST_H
#define MST_H

#include "csr.h"

typedef struct {
    long long total_weight;
    int edge_count;
    int connected;
} MSTResult;

MSTResult kruskal_mst(const CSRGraph *graph);
MSTResult prim_mst(const CSRGraph *graph, int start);

#endif
