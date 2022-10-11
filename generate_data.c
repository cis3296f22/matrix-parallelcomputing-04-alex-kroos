
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mat.h"
#include <sys/time.h>
// SIMD: Single Instruction Multiple Data
// OMP: OpenMP -> an application programming interface that supports multi-platform shared-memory multiprocessing programming in C,
// MPI: Message Passing Interface


int generate_data(int matrix_size, char *output_filename)
{
    FILE *fp;
    // deletes contents of file
  
    fp = fopen(output_filename, "a");

    struct timeval stop, start;
    int rows, cols;

    rows = matrix_size;
    cols = matrix_size;
    double *a, *b, *result;
    
    result = malloc(rows * cols * sizeof(double));
    a = gen_matrix(rows, cols);
    b = gen_matrix(rows, cols);
    
    gettimeofday(&start, NULL);
    mmult(result, a, rows, cols, b, rows, cols);
    gettimeofday(&stop, NULL);

    // this is in seconds
    double time_taken = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

    fprintf(fp, "\n%f, %d", time_taken * 1000  , matrix_size);
    fclose(fp);
    free(result);
    free(a);
    free(b);
}

int main()
{

    for (int i = 5; i < 500; i += 5)
    {
        printf("tested matrix size %d\n", i);
        generate_data(i, "data/mmult_simd.out");
    }
}
