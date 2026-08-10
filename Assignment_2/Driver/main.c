#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#include "../Include/csr.h"
#include "../Include/Bellman_ford.h"
#include "../Include/floyd_warshall.h"

static void print_usage(const char *program)
{
    printf("Usage:\n");
    printf("  %s bf <input_file>\n", program);
    printf("  %s fw <input_file>\n", program);
}

static int read_bellman_ford_file(const char *fn,CSRGraph **graph,int *src){
    
    FILE *file = fopen(fn, "r");
    if (file == NULL){
        printf("Error: Cannot open input file: %s\n",fn);
        return 0;
    }
    int V, E;

    if (fscanf(file, "%d %d", &V, &E) != 2){
        printf("Error: Invalid Bellman-Ford header.\n");
        fclose(file);
        return 0;
    }

    if (V <= 0 || E < 0){
        printf("Error: Invalid V or E.\n");
        fclose(file);
        return 0;
    }

    int **adjacency =malloc(V * sizeof(int *));
    int *degree =calloc(V, sizeof(int));

    if (adjacency == NULL || degree == NULL){
        printf("Error: Memory allocation failed.\n");
        free(adjacency);
        free(degree);
        fclose(file);
        return 0;
    }

    for (int i = 0; i < V; i++){
        adjacency[i] = NULL;
    }

    for (int u = 0; u < V; u++){
        int vertex;
        int d;

        if (fscanf(file, "%d %d", &vertex, &d) != 2){
            printf("Error: Invalid adjacency list.\n");
            for (int i = 0; i < V; i++){
                free(adjacency[i]);
            }
            free(adjacency);
            free(degree);
            fclose(file);
            return 0;
        }

        if (vertex < 0 || vertex >= V || d < 0){
            printf("Error: Invalid vertex or degree.\n");
            for (int i = 0; i < V; i++){
                free(adjacency[i]);
            }
            free(adjacency);
            free(degree);
            fclose(file);
            return 0;
        }

        degree[vertex] = d;

        if (d > 0){
            adjacency[vertex] = malloc(2 * d * sizeof(int));
            if (adjacency[vertex] == NULL){
                printf("Error: Memory allocation failed.\n");
                for (int i = 0; i < V; i++){
                    free(adjacency[i]);
                }
                free(adjacency);
                free(degree);
                fclose(file);
                return 0;
            }

            for (int j = 0; j < d; j++){
                int neighbour;
                int weight;

                if (fscanf(file,"%d %d",&neighbour,&weight) != 2){
                    printf("Error: Invalid edge data.\n");

                    for (int i = 0; i < V; i++){
                        free(adjacency[i]);
                    }
                    free(adjacency);
                    free(degree);
                    fclose(file);
                    return 0;
                }

                if (neighbour < 0 ||neighbour >= V){
                    printf("Error: Invalid neighbour.\n");
                    for (int i = 0; i < V; i++){
                        free(adjacency[i]);
                    }
                    free(adjacency);
                    free(degree);
                    fclose(file);
                    return 0;
                }
                adjacency[vertex][2 * j] =   neighbour;
                adjacency[vertex][2 * j + 1] = weight;
            }
        }
    }

    char src_word[32];

    if (fscanf(file, "%31s %d", src_word, src) != 2){
        printf("Error: Missing src line.\n");
        for (int i = 0; i < V; i++){
            free(adjacency[i]);
        }
        free(adjacency);
        free(degree);
        fclose(file);
        return 0;
    }

    if (strcmp(src_word, "src") != 0){
        printf("Error: Expected src keyword.\n");

        for (int i = 0; i < V; i++){
            free(adjacency[i]);
        }
        free(adjacency);
        free(degree);
        fclose(file);
        return 0;
    }

    if (*src < 0 || *src >= V){
        printf("Error: Invalid src vertex.\n");
        for (int i = 0; i < V; i++){
            free(adjacency[i]);
        }
        free(adjacency);
        free(degree);
        fclose(file);
        return 0;
    }

    *graph = create_csr(V, E, adjacency, degree);

    for (int i = 0; i < V; i++){
        free(adjacency[i]);
    }
    free(adjacency);
    free(degree);
    fclose(file);

    if (*graph == NULL){
        printf("Error: CSR creation failed.\n");
        return 0;
    }

    return 1;
}

static long long **allocate_matrix(int V){
    long long **matrix = malloc(V * sizeof(long long *));

    if (matrix == NULL){
        return NULL;
    }

    for (int i = 0; i < V; i++){
        matrix[i] = malloc(V * sizeof(long long));

        if (matrix[i] == NULL){
            for (int j = 0; j < i; j++){
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}


static void free_matrix(long long **matrix , int V){
    if (matrix == NULL)
     return;

    for (int i = 0; i < V; i++){
        free(matrix[i]);
    }
    free(matrix);
}

static int read_floyd_file( const char *fn , int *V , long long ***matrix ){
    FILE *file = fopen(fn, "r");
    if (file == NULL){
        printf("Error: Cannot open input file: %s\n",
               fn);
        return 0;}

    if (fscanf(file, "%d", V) != 1){
        printf("Error: Invalid Floyd-Warshall header.\n");
        fclose(file);
        return 0;
    }

    if (*V <= 0){
        printf("Error: Invalid number of vertices.\n");
        fclose(file);
        return 0;
    }

    *matrix = allocate_matrix(*V);

    if (*matrix == NULL){
        printf("Error: Matrix allocation failed.\n");
        fclose(file);
        return 0;
    }

    for (int i = 0; i < *V; i++)
{
    for (int j = 0; j < *V; j++)
    {
        char token[64];

        if (fscanf(file, "%63s", token) != 1)
        {
            printf("Error: Invalid matrix data.\n");

            free_matrix(*matrix, *V);
            fclose(file);

            return 0;
        }

        if (strcmp(token, "INF") == 0)
        {
            (*matrix)[i][j] = FW_INF;
        }
        else
        {
            char *endptr;

            long long value =
                strtoll(token, &endptr, 10);

            if (*endptr != '\0')
            {
                printf("Error: Invalid matrix value.\n");

                free_matrix(*matrix, *V);
                fclose(file);

                return 0;
            }

            (*matrix)[i][j] = value;
        }
    }
}

fclose(file);
return 1;
}

static int run_bellman_ford(const char *fn){
    CSRGraph *graph = NULL;
    int src;

    if (!read_bellman_ford_file(fn,&graph,&src)){
        return 1;
    }
    long long *distance = malloc(graph->V * sizeof(long long));
    
    if (distance == NULL){
        printf("Error: Memory allocation failed.\n");
        free_csr(graph);
        return 1;
    }

    clock_t start = clock();
    int negative_cycle = bellman_ford(graph,src,distance);
    clock_t end = clock();
    double time_ms =((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("\n");
    printf("Algorithm: Bellman-Ford\n");
    printf("src: %d\n", src);

    if (negative_cycle){
        printf("Negative cycle: true\n");
    }
    else{
        printf("Vertex Distance\n");
        for (int i = 0; i < graph->V; i++){
            printf("%d ", i);
            if (distance[i] == LLONG_MAX){
                printf("INF\n");
            }
            else{
                printf("%lld\n",distance[i]);
            }
        }
        printf("Negative cycle: none\n");
    }

    printf("Execution time: %.6f ms\n",time_ms );
    free(distance);
    free_csr(graph);
    return 0;
}

static int run_floyd_warshall(const char *fn){
    int V;
    long long **matrix = NULL;

    
    if (!read_floyd_file(fn,&V,&matrix)){
        return 1;
    }
    clock_t start = clock();
    int negative_cycle = floyd_warshall(V, matrix);
    clock_t end = clock();

    double time_ms =((double)(end - start) /CLOCKS_PER_SEC) * 1000.0;
    printf("\n");
    printf("Algorithm: Floyd-Warshall\n");

    if (negative_cycle){
        printf("Negative cycle: true\n");
    }
    else{
        printf("Distance matrix:\n");

        for (int i = 0; i < V; i++){
            for (int j = 0; j < V; j++){
                if (matrix[i][j] == FW_INF){
                    printf("INF");
                }
                else{
                    printf("%lld",matrix[i][j]);
                }
                if (j < V - 1){
                    printf(" ");
                }
            }

            printf("\n");
        }

        printf("Negative cycle: none\n");
    }

    printf("Execution time: %.6f ms\n",time_ms);
    free_matrix(matrix, V);
    return 0;
}


int main(int argc, char *argv[]){
    if (argc != 3){
        print_usage(argv[0]);
        return 1;
    }

    const char *algorithm = argv[1];
    const char *fn = argv[2];

    if (strcmp(algorithm, "bf") == 0){
        return run_bellman_ford(fn);
    }

    if (strcmp(algorithm, "fw") == 0){
        return run_floyd_warshall(fn);
    }

    printf("Error: Unknown algorithm '%s'\n",algorithm);
    print_usage(argv[0]);
    return 1;
}