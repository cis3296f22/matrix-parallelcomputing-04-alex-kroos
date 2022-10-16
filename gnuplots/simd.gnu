set terminal png size 800,600 
set output 'photos/simd.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix size'
set ylabel 'Time (msec)'
set title 'Matrix multiplication: SIMD'
plot  "data/mmult_simd.out"  title 'mmult simd' with lines
