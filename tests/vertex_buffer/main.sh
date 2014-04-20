echo "Method Draw Swap" > header
echo -e "Immediate\nInterleaved\nSeparate" > titles
grep 'Median draw time:' immediate interleaved separate | cut -d':' -f3 > draw
grep 'Median swap time:' immediate interleaved separate | cut -d':' -f3 > swap
paste titles draw swap > table
cat table > vertex_buffer.dat
gnuplot main.gpi 
