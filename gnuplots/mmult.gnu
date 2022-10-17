set terminal png size 800,600 
set output 'photos/mmult.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix size'
set ylabel 'Time (msec)'
set title 'Matrix multiplication: mmmult'
plot  "data/mmult.out"  title 'mmult' with lines
