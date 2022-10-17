#!/bin/bash

## THIS GENERATES ALL THE DATA NEEDED 

# no simd
echo "Testing no simd"
gcc mat.c mmult.c generate_data.c -o generate_data && ./generate_data "data/nosimd.out" 
echo "Finished no simd"

# simd
echo "Testing  simd"
gcc mat.c mmult_simd.c generate_data.c -o generate_data && ./generate_data "data/simd.out" 
echo "Finished simd"


# no O3
echo "Testing  no O3"
gcc mat.c mmult_simd.c generate_data.c -o generate_data && ./generate_data "data/noO3.out" 
echo "Finished no O3"

#  O3
echo "Testing O3"
gcc -O3 mat.c mmult_simd.c  generate_data.c -o generate_data && ./generate_data "data/O3.out" 
echo "Finished O3"


# OMP
echo "Testing OMP"
gcc -fopenmp -O3 mat.c mmult_omp.c generate_data.c -o generate_data && ./generate_data "data/omp.out"
echo "Finished OMP"

# MPI & OMP
echo "Testing MPI & OMP"
for ((i=5; i<500; i+=5))
do
    mpicc -fopenmp -O3 mat.c mmult_mpi.c -o mpi &&  ./mpi $i
done
echo "Finished MPI & OMP"

# removes the executable 
rm generate_data

# Generates the graph
gnuplot gnuplots/main_graph.gnu