#include <stdlib.h>
#include "../Include/mst.h"

typedef struct {
    int u, v, w;
} Edge;

typedef struct {
    int *parent;
    int *rank;
} DSU;

static int dsu_find(DSU *d, int x)
{
    if (d->parent[x] != x)
        d->parent[x] = dsu_find(d, d->parent[x]);
    return d->parent[x];
}

static int dsu_union(DSU *d, int a, int b)
{
    a = dsu_find(d, a);
    b = dsu_find(d, b);
    if (a == b) return 0;

    if (d->rank[a] < d->rank[b]) {
        int t = a; a = b; b = t;
    }
    d->parent[b] = a;
    if (d->rank[a] == d->rank[b]) d->rank[a]++;
    return 1;
}

static int compare_edges(const void *pa, const void *pb)
{
    const Edge *a = pa;
    const Edge *b = pb;
    if (a->w != b->w) return (a->w > b->w) - (a->w < b->w);
    if (a->u != b->u) return (a->u > b->u) - (a->u < b->u);
    return (a->v > b->v) - (a->v < b->v);
}

MSTResult kruskal_mst(const CSRGraph *g)
{
    MSTResult result = {0, 0, 0};
    if (g == NULL || g->v == 0) {
        result.connected = 1;
        return result;
    }

    int max_edges = g->E > 0 ? g->E : 1;
    Edge *edges = malloc((size_t)max_edges * sizeof(Edge));
    int count = 0;

    if (edges == NULL) return result;

    for (int u = 0; u < g->v; ++u) {
        for (int p = g->row_ptr[u]; p < g->row_ptr[u + 1]; ++p) {
            int v = g->col_idx[p];
            if (u < v && count < max_edges)
                edges[count++] = (Edge){u, v, g->values[p]};
        }
    }

    qsort(edges, (size_t)count, sizeof(Edge), compare_edges);

    DSU d;
    d.parent = malloc((size_t)g->v * sizeof(int));
    d.rank = calloc((size_t)g->v, sizeof(int));
    if (d.parent == NULL || d.rank == NULL) {
        free(d.parent); free(d.rank); free(edges);
        return result;
    }
    for (int i = 0; i < g->v; ++i) d.parent[i] = i;

    for (int i = 0; i < count && result.edge_count < g->v - 1; ++i) {
        if (dsu_union(&d, edges[i].u, edges[i].v)) {
            result.total_weight += edges[i].w;
            result.edge_count++;
        }
    }

    result.connected = (result.edge_count == g->v - 1);
    free(d.parent);
    free(d.rank);
    free(edges);
    return result;
}

typedef struct HeapNode {
    long long key;
    int vertex;
} HeapNode;

typedef struct {
    HeapNode *a;
    int size;
    int capacity;
} MinHeap;

static void heap_swap(HeapNode *a, HeapNode *b)
{
    HeapNode t = *a; *a = *b; *b = t;
}

static int heap_push(MinHeap *h, long long key, int vertex)
{
    if (h->size == h->capacity) {
        int newcap = h->capacity == 0 ? 16 : h->capacity * 2;
        HeapNode *tmp = realloc(h->a, (size_t)newcap * sizeof(HeapNode));
        if (tmp == NULL) return 0;
        h->a = tmp;
        h->capacity = newcap;
    }
    int i = h->size++;
    h->a[i] = (HeapNode){key, vertex};
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->a[p].key <= h->a[i].key) break;
        heap_swap(&h->a[p], &h->a[i]);
        i = p;
    }
    return 1;
}

static HeapNode heap_pop(MinHeap *h)
{
    HeapNode result = h->a[0];
    h->a[0] = h->a[--h->size];
    int i = 0;
    while (1) {
        int l = 2 * i + 1, r = l + 1, smallest = i;
        if (l < h->size && h->a[l].key < h->a[smallest].key) smallest = l;
        if (r < h->size && h->a[r].key < h->a[smallest].key) smallest = r;
        if (smallest == i) break;
        heap_swap(&h->a[i], &h->a[smallest]);
        i = smallest;
    }
    return result;
}

MSTResult prim_mst(const CSRGraph *g, int start)
{
    MSTResult result = {0, 0, 0};
    if (g == NULL || g->v == 0) {
        result.connected = 1;
        return result;
    }
    if (start < 0 || start >= g->v) start = 0;

    const long long INF = 0x3fffffffffffffffLL;
    long long *key = malloc((size_t)g->v * sizeof(long long));
    int *used = calloc((size_t)g->v, sizeof(int));
    MinHeap heap = {0};
    if (key == NULL || used == NULL) {
        free(key); free(used); return result;
    }

    for (int i = 0; i < g->v; ++i) key[i] = INF;
    key[start] = 0;
    heap_push(&heap, 0, start);

    while (heap.size > 0) {
        HeapNode node = heap_pop(&heap);
        int u = node.vertex;
        if (used[u]) continue;
        used[u] = 1;

        if (node.key != 0 || u != start) {
            if (node.key < INF) {
                result.total_weight += node.key;
                result.edge_count++;
            }
        }

        for (int p = g->row_ptr[u]; p < g->row_ptr[u + 1]; ++p) {
            int v = g->col_idx[p];
            int w = g->values[p];
            if (!used[v] && (long long)w < key[v]) {
                key[v] = w;
                heap_push(&heap, key[v], v);
            }
        }
    }

    result.connected = (result.edge_count == g->v - 1);
    free(heap.a);
    free(key);
    free(used);
    return result;
}
