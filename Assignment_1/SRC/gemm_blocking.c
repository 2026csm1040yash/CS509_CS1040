#include "gemm_blocking.h"

#define BLOCK_SIZE 32

void gemm_blocking(int M, int K, int N,
                   int A[M][K],
                   int B[K][N],
                   int C[M][N])
{
    int curr_row_in_block;
    int curr_col_in_block;
    int curr_multi_index_in_block;

    int row_curr_block;
    int col_curr_block;
    int index_curr_block;

    /* Initialize Result Matrix */
    for (curr_row_in_block = 0; curr_row_in_block < M; curr_row_in_block++)
    {
        for (curr_col_in_block = 0; curr_col_in_block < N; curr_col_in_block++)
        {
            C[curr_row_in_block][curr_col_in_block] = 0;
        }
    }

    /* Blocked Matrix Multiplication */
    for (row_curr_block = 0; row_curr_block < M; row_curr_block += BLOCK_SIZE)
    {
        for (index_curr_block = 0; index_curr_block < K; index_curr_block += BLOCK_SIZE)
        {
            for (col_curr_block = 0; col_curr_block < N; col_curr_block += BLOCK_SIZE)
            {
                int row_end = row_curr_block + BLOCK_SIZE;
                if (row_end > M)
                    row_end = M;

                int index_end = index_curr_block + BLOCK_SIZE;
                if (index_end > K)
                    index_end = K;

                int col_end = col_curr_block + BLOCK_SIZE;
                if (col_end > N)
                    col_end = N;

                for (curr_row_in_block = row_curr_block;
                     curr_row_in_block < row_end;
                     curr_row_in_block++)
                {
                    for (curr_multi_index_in_block = index_curr_block;
                         curr_multi_index_in_block < index_end;
                         curr_multi_index_in_block++)
                    {
                        int temp =
                            A[curr_row_in_block][curr_multi_index_in_block];

                        for (curr_col_in_block = col_curr_block;
                             curr_col_in_block < col_end;
                             curr_col_in_block++)
                        {
                            C[curr_row_in_block][curr_col_in_block] +=
                                temp *
                                B[curr_multi_index_in_block][curr_col_in_block];
                        }
                    }
                }
            }
        }
    }
}