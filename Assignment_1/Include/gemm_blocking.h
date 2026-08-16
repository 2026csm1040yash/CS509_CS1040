#ifndef GEMM_BLOCKING_H
#define GEMM_BLOCKING_H

void gemm_blocking(int X, int Y, int Z,
          int A[X][Y],
          int B[Y][Z],
          int C[X][Z]);

#endif