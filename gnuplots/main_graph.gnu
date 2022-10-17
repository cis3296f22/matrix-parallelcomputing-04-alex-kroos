set terminal png size 800,600 
set output 'photos/main.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix size'
set ylabel 'Time (msec)'
set title 'Matrix multiplication: Main Graph'
plot  "data/nosimd.out"  title 'nosimd' with lines, "data/simd.out"  title 'simd' with lines, "data/O3.out" \
  title 'O3' with lines,"data/noO3.out"  title 'no O3' with lines, "data/omp.out" title "omp" with lines

