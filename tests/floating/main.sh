echo "Type GLfloat GLdouble" > 'floating.dat'	
grep "primitives" float | cut -d'(' -f2 | cut -d' ' -f1 > 'primitive_counts'
grep "Median draw time:" float	 | cut -d: -f2 > 'float_medians'
grep "Median draw time:" double | cut -d: -f2 > 'double_medians'
paste primitive_counts float_medians double_medians > 'table'
cat table >> floating.dat
gnuplot main.gpi
