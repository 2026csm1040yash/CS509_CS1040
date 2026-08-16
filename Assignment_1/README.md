# CS509 Assignment 1

## Algorithms

### Individual Task
- Simple GEMM
- Blocking GEMM


## GEMM Cache Optimization

The blocked GEMM implementation uses a block size of **32**.

Initially, the nested loop ordering used was

```
ii -> jj -> kk
```

After performance analysis, the loop ordering was changed to

```
ii -> kk -> jj
```

### Observation

The **ii → kk → jj** ordering improves cache utilization because:

- Matrix **A** elements remain in cache longer.
- Better reuse of cache lines.
- Reduced cache misses.
- Improved temporal and spatial locality.
- Lower execution time for medium and large matrices.

For small matrices, both loop orders perform similarly.

---


# Timing

Only the algorithm execution time is measured.

The following operations are **NOT** included:

- File reading
- Input parsing
- Output generation
- Output file writing

Timing begins immediately before calling the algorithm and stops immediately after the algorithm completes.

---

# Algorithm Summary

## Simple GEMM

- Standard triple nested-loop matrix multiplication.
- Time Complexity: **O(M × K × N)**

---

## Blocking GEMM

- Matrix multiplication using cache blocking.
- Improves cache locality.
- Same output as Simple GEMM.
- Faster for larger matrices.

---


# GEMM Results

| Test Cases              |       Simple Time | Blocking Time | Status |
|------------------------:|------------------:|--------------:|:------:|
| gemm_test_case_50_x_50.txt   |  328.00 ms   |  264.00 ms     |Pass |
| gemm_test_case_90_x_100.txt  |  2485.00 ms  |  1982.00ms     |Pass |
| gemm_test_case_256_x_256.txt |  49902.00 ms |  33291.00 ms   |Pass |

# Observations

- Blocking GEMM improves cache reuse.
- Changing the loop order from **ii → jj → kk** to **ii → kk → jj** reduces cache misses and improves execution time for larger matrices.
- The performance improvement becomes more noticeable as matrix size increases.