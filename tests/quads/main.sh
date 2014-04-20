grep "primitives" quads | cut -d'(' -f2 | cut -d' ' -f1 > 'primitive_counts'
grep 'Median draw time:' quads | cut -d':' -f2 > draw
grep 'Median swap time:' quads | cut -d':' -f2 > swap
paste primitive_counts draw swap > table
cat table > quads.dat 
gnuplot main.gpi 
