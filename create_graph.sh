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
gcc mat.c mmult.c generate_data.c -o generate_data && ./generate_data "data/noO3.out" 
echo "Finished no O3"

#  O3
echo "Testing O3"
gcc -O3 mat.c mmult.c generate_data.c -o generate_data && ./generate_data "data/O3.out" 
echo "Finished O3"

# removes the executable 
rm generate_data

# Generates the graph
gnuplot gnuplots/main_graph.gnu