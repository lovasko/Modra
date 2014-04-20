echo -e "Blending\nTextures\nLights\nWireframe\nAll" > titles
grep 'Median draw time:' blending textures light wireframe all  | cut -d':' -f3 > draw
grep 'Median swap time:' blending textures light wireframe all  | cut -d':' -f3 > swap 
paste titles draw swap > table
cat table > various.dat 
gnuplot main.gpi 
