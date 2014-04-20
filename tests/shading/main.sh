echo -e "Flat\nSmooth" > titles
grep 'Median draw time:' flat smooth | cut -d':' -f3 > draw
grep 'Median swap time:' flat smooth | cut -d':' -f3 > swap
paste titles draw swap > table
cat table > shading.dat 
gnuplot main.gpi 
