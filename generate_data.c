
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mat.h"
#include <stdint.h>	
#define BILLION 1000000000L
// SIMD: Single Instruction Multiple Data
// OMP: OpenMP -> an application programming interface that supports multi-platform shared-memory multiprocessing programming in C,
// MPI: Message Passing Interface

int generate_data( FILE* fp, int matrix_size)
{
    struct timespec start;
    struct timespec end;
    int rows, cols;

    rows = matrix_size;
    cols = matrix_size;
    double *a, *b, *result;
    
    result = malloc(rows * cols * sizeof(double));
    a = gen_matrix(rows, cols);
    b = gen_matrix(rows, cols);
    
    clock_gettime(CLOCK_REALTIME, &start);
    mmult(result, a, rows, cols, b, rows, cols);
    clock_gettime(CLOCK_REALTIME, &end);

    uint64_t diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    // milliseconds 
    fprintf(fp, "\n%d, %d",   diff / (uint64_t) 1e6,matrix_size );
    free(result);
    free(a);
    free(b);
}

int main()
{
    char * output_filename = "data/mmult.out";
    FILE *fp =  fopen(output_filename, "w");
    for (int i = 5; i < 500; i += 5)
    {
        printf("tested matrix size %d\n", i);
        generate_data(fp, i);
    }
    fclose(fp);
}
