#include <stdio.h>

void gemm(int M, int K, int N,
          int A[M][K],
          int B[K][N],
          int C[M][N])
{
    int i, j, k;

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            C[i][j] = 0;

            for (k = 0; k < K; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}