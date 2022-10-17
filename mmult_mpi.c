#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include "mpi.h"
#define BILLION 1000000000L

int mmult(double *c,
          double *a, int aRows, int aCols,
          double *b, int bRows, int bCols)
{
    int i, j, k;
    // Insert your code here
#pragma omp parallel default(none) shared(a, b, c, aRows, aCols, bRows, bCols) private(i, k, j)
#pragma omp for
    for (i = 0; i < aRows; i++)
    {
        for (j = 0; j < bCols; j++)
            c[i * bCols + j] = 0;
        for (k = 0; k < aRows; k++)
            for (j = 0; j < bCols; j++)
                c[i * bCols + j] += a[i * aCols + k] * b[k * bCols + j];
    }

    return 0;
}

int main(int argc, char **argv)
{
    int myid, numprocs;
    FILE *fp = fopen("./data/mpi.out", "w");
    double *a, *b, *result;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    for (int i = 5; i < 500; i += 5)
    {
        struct timespec start, end;
        int rows, cols;
        rows = cols = i;
        result = malloc(rows * cols * sizeof(double));
        a = gen_matrix(rows, cols);
        b = gen_matrix(rows, cols);
        clock_gettime(CLOCK_REALTIME, &start);
        mmult(result, a, rows, cols, b, rows, cols);
        clock_gettime(CLOCK_REALTIME, &end);
        uint64_t diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
        // milliseconds
        fprintf(fp, "\n%d, %d", rows, diff / (uint64_t)1e6);
        free(result);
        free(a);
        free(b);
    }
}