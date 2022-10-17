set terminal png size 800,600 
set output 'photos/nosimd_vs_simd.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix size'
set ylabel 'Time (msec)'
set title 'Matrix multiplication: NOSIMD VS SIMD'
plot  "data/mmult.out"  title 'nosimd' with lines,     "data/mmult_simd.out"  title 'simd' with lines
