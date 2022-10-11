set terminal png size 800,600 
set output 'photos/main.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix size'
set ylabel 'Time (msec)'
set title 'Matrix multiplication: SIMD VS NOSIMD'
plot  "data/mmult.out"  title 'mmult' with lines, "data/mmult_simd.out"  title 'mmult simd' with lines,"data/mmult_parallelization.out"  title 'mmult parallelization' with lines,"data/mmult_simd_vectorized.out"  title 'mmult simd vectorized' with lines
