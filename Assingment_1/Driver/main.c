#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../Include/gemm.h"
#include "../Include/gemm_blocking.h"

int main()
{
    FILE *fp;

    int M, K, N;
    int i, j;

    fp = fopen("Testcases/gemm_test_cases/gemm_test_case_90x100_100x110.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening input file.\n");
        return 1;
    }

    /* Read matrix dimensions */
    fscanf(fp, "%d %d %d", &M, &K, &N);

    /* Variable Length Arrays (C99) */
    int A[M][K];
    int B[K][N];
    int C[M][N];

    /* Read Matrix A */
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < K; j++)
        {
            fscanf(fp, "%d", &A[i][j]);
        }
    }

    /* Read Matrix B */
    for (i = 0; i < K; i++)
    {
        for (j = 0; j < N; j++)
        {
            fscanf(fp, "%d", &B[i][j]);
        }
    }

    fclose(fp);

    /* -------- Timing starts here -------- */

    clock_t start = clock();

for (int run = 0; run < 1000; run++)
{
    // gemm(M, K, N, A, B, C);
    // /* OR
      gemm_blocking(M, K, N, A, B, C);
    // */
}

    clock_t end = clock();

    

    /* -------- Timing ends here -------- */

    double execution_time =
        ((double)(end - start)* 1000) / CLOCKS_PER_SEC ;

    /* Print Result Matrix */

    printf("Result Matrix:\n");

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", C[i][j]);
        }

        printf("\n");
    }

    printf("\nExecution Time : %.2f ms\n", execution_time);

    return 0;
}