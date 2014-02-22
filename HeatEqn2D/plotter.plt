set terminal png size 1024, 800
set output 'OUTFILE.png'
set title 'OUTFILE'
set xlabel "x"
set ylabel "y"

#box params
set zrange [0:2]
set xrange [0:1]
set yrange [0:1]

#circle params
set xrange [-1.2:1.2]
set yrange [-1.2:1.2]
set zrange [-.5:.5]
#plot 'INFILE.dat' with lines
splot 'INFILE.dat' with lines
