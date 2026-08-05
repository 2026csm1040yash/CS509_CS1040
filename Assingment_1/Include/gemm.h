#ifndef GEMM_H
#define GEMM_H

void gemm(int X, int Y, int Z,
          int A[X][Y],
          int B[Y][Z],
          int C[X][Y]);

#endif