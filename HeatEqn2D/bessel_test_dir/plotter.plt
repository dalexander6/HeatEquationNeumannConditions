set terminal png size 1024, 800
set output 'OUTFILE.png'
set title 'OUTFILE'
set yrange [-.4:1]

#plot 'INFILE.dat' with lines
plot 'INFILE.dat' 
