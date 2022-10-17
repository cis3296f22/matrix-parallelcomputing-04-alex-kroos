/**
 * Incomplete program to multiply a matrix times a matrix using both
 * MPI to distribute the computation among nodes and OMP
 * to distribute the computation among threads.
 */

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

#include "mat.h"

int main(int argc, char* argv[])
{
    int nrows, ncols;
    double *aa, *b, *c;	/* the A matrix */
    double *bb;	/* the B matrix */
    double *cc1;	/* A x B computed using the omp-mpi code you write */
    double *cc2;	/* A x B computed using the conventional algorithm */
    int myid, numprocs;
    double starttime, endtime;
    MPI_Status status;
    double *buffer, ans;
    /* insert other global variables here */
    int i, j, numsent, sender;
    int anstype, row;
    srand(time(0));

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (argc > 1) {
        nrows = atoi(argv[1]);
        ncols = nrows;

        if (myid == 0) 
        {
            // Controller Code goes here
            aa = gen_matrix(nrows, ncols);
            bb = gen_matrix(ncols, nrows);
            cc1 = malloc(sizeof(double) * nrows * nrows);
            starttime = MPI_Wtime();

            /* Insert your controller code here to store the product into cc1 */
            numsent = 0;
            MPI_Bcast(b, ncols, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            for (i = 0; i < min(numprocs-1, nrows); i++) {
                for (j = 0; j < ncols; j++) {
                  buffer[j] = aa[i * ncols + j];
            }
            MPI_Send(buffer, ncols, MPI_DOUBLE, i+1, i+1,MPI_COMM_WORLD);
            numsent++;
            }

            for (i = 0; i < nrows; i++)
            {
                MPI_Recv(&ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                sender = status.MPI_SOURCE;
                anstype = status.MPI_TAG;
                c[anstype-1] = ans;

                //calculation
                if (numsent < nrows) {
                  for (j = 0; j < ncols; j++) 
                    buffer[j] = aa[numsent*ncols + j];
                
                //sedning the parts to the other worker 
                MPI_Send(buffer, ncols, MPI_DOUBLE, sender, numsent+1,
                        MPI_COMM_WORLD);
                numsent++;
                }else {MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0,MPI_COMM_WORLD);}
            }

            endtime = MPI_Wtime();
            
            cc2  = malloc(sizeof(double) * nrows * nrows);
            mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
            compare_matrices(cc2, cc1, nrows, nrows);
        } 
        else 
        {
        // Worker code goes here
        MPI_Bcast(b, ncols, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        if (myid <= nrows) {
            while(1) 
            {
                //recving buffer(the matrix) from the sender
                MPI_Recv(buffer, ncols, MPI_DOUBLE, 0,
                MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                
                //if the host sends out a zero then we stop this loop
                if (status.MPI_TAG == 0){break;}
                
                row = status.MPI_TAG;
                ans = 0.0;
                
                //OMP
                #pragma omp shared(ans) for reduction(+:ans)
                for (j = 0; j < ncols; j++)
                    ans += buffer[j] * b[j];
                MPI_Send(&ans, 1, MPI_DOUBLE, 0, row,MPI_COMM_WORLD);
            }
        } 
    }
    }else {fprintf(stderr, "Usage matrix_times_vector <size>\n");}


    MPI_Finalize();
    return 0;
}
