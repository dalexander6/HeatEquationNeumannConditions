set terminal png size 1024, 800
set output 'OUTFILE.png'
set title 'OUTFILE'
set xlabel "x"
set ylabel "y"

set zrange [-.01:2]
set xrange [-.2:1.2]
set yrange [-.2:1.2]
set pm3d
set isosamples 50
set palette defined (0 "purple", 1 "red", 2 "yellow")
set cbrange [0:2]

unset surface
set nokey
unset title
splot '<awk -f addblanks.awk INFILE.dat'
