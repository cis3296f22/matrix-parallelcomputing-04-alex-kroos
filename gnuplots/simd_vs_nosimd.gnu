set terminal png size 800,600 
set output 'photos/simd_vs_nosimd.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix size'
set ylabel 'Time (msec)'
set title 'Matrix multiplication: SIMD VS NOSIMD'
plot  "mmult.out"  title 'mmult' with lines,"mmult_simd.out"  title 'mult_simd.out' with lines 
