#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Include/csr.h"
#include "../Include/mst.h"

static int read_graph(const char *fn, CSRGraph **out_graph)
{
    FILE *fp = fopen(fn, "r");
    if (!fp) return 0;

    int V, E;
    if (fscanf(fp, "%d %d", &V, &E) != 2 || V <= 0 || E < 0) {
        fclose(fp);
        return 0;
    }

    int **adjacency = calloc((size_t)V, sizeof(int *));
    int *degree = calloc((size_t)V, sizeof(int));
    if (!adjacency || !degree) {
        free(adjacency);
        free(degree);
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < V; ++i) {
        int u, d;
        if (fscanf(fp, "%d %d", &u, &d) != 2 || u < 0 || u >= V || d < 0)
            goto fail;

        degree[u] = d;
        if (d > 0) {
            adjacency[u] = malloc((size_t)(2 * d) * sizeof(int));
            if (!adjacency[u]) goto fail;

            for (int j = 0; j < d; ++j) {
                int v, w;
                if (fscanf(fp, "%d %d", &v, &w) != 2 || v < 0 || v >= V)
                    goto fail;
                adjacency[u][2 * j] = v;
                adjacency[u][2 * j + 1] = w;
            }
        }
    }

    fclose(fp);
    *out_graph = create_csr(V, E, adjacency, degree);

    for (int i = 0; i < V; ++i) free(adjacency[i]);
    free(adjacency);
    free(degree);

    return *out_graph != NULL;

fail:
    for (int i = 0; i < V; ++i) free(adjacency[i]);
    free(adjacency);
    free(degree);
    fclose(fp);
    return 0;
}

static void get_output_fn(const char *algorithm,
                                const char *input_file,
                                char *output,
                                size_t output_size)
{
    const char *base = strrchr(input_file, '/');
#ifdef _WIN32
    const char *win_base = strrchr(input_file, '\\');
    if (win_base && (!base || win_base > base)) base = win_base;
#endif
    base = base ? base + 1 : input_file;

    char name[256];
    snprintf(name, sizeof(name), "%s", base);
    char *dot = strrchr(name, '.');
    if (dot) *dot = '\0';

    snprintf(output, output_size, "Output/%s_%s.txt", algorithm, name);
}

int main(int argc, char **argv)
{
    if (argc != 3) return 1;

    CSRGraph *graph = NULL;
    if (!read_graph(argv[2], &graph)) return 1;

    MSTResult result;
    clock_t start = clock();

    if (strcmp(argv[1], "kruskal") == 0) {
        result = kruskal_mst(graph);
    } else if (strcmp(argv[1], "prim") == 0) {
        result = prim_mst(graph, 0);
    } else {
        free_csr(graph);
        return 1;
    }

    clock_t end = clock();
    double time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    char output_file[512];
    get_output_fn(argv[1], argv[2], output_file, sizeof(output_file));

    FILE *out = fopen(output_file, "w");
    if (!out) {
        free_csr(graph);
        return 1;
    }

    fprintf(out, "MST total weight: %lld\n", result.total_weight);
    fprintf(out, "MST edges: %d\n", result.edge_count);
    fprintf(out, "Connected graph: %s\n", result.connected ? "true" : "false");
    fprintf(out, "Execution time: %.6f ms\n", time_ms);
    fclose(out);

    /* Terminal contains only the result and measured execution time. */
    printf("MST total weight: %lld\n", result.total_weight);
    printf("MST edges: %d\n", result.edge_count);
    printf("Connected graph: %s\n", result.connected ? "true" : "false");
    printf("Execution time: %.6f ms\n", time_ms);

    free_csr(graph);
    return 0;
}
