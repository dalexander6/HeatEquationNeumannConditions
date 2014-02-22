#set terminal pngcairo size 1024, 600
set termoption dash
set key font ",12" spacing 2 
set key box
set key opaque
set key width -3
set yrange [0:2]
set xrange [-.5:2]
set xlabel "$x$"
set ylabel "$v$" offset 2
set style line 1 lc rgb "black" lt 2 lw 3 pt 1 #black + signs
set style line 2 lc rgb "black" lt 2 lw 3 #dashed black line
set style line 3 lc rgb "black" lt 1 lw 3 #solid black line
set style line 4 lc rgb "black" lt 3 lw 3 pt 9 #dotted black line
plot 'HeatApproxU0000.dat' ls 2 title '$v$ at $t = 0$'
replot 'HeatApproxU0100.dat' with lines ls 3 title '$v$ at $t = 0.015$'
set terminal epslatex standalone size 5in, 3in
#set output 'v.png'
set output 'v1DN100.tex'
replot 'HeatApproxU0600.dat' with lines ls 4 t '$v$ at $t = 0.09$'
set out

set xrange [0:1]
set ylabel "$u$"
set key bottom right
unset terminal
plot 'HeatTrueU0000.dat' ls 2 title '$u$ at $t = 0$'
#replot 'HeatTrueU0050.dat' with lines ls 2 title '$u$ at $t = 0.0075$'
replot 'HeatTrueU0100.dat' with lines ls 3 title '$u$ at $t = 0.015$'
set terminal epslatex standalone size 5in, 3in
set output 'u1D.tex'
replot 'HeatTrueU0600.dat' with lines ls 4 t '$u$ at $t = 0.09'

#compoile via cat pic_creator.plt | gnuplot
# and then rubber --pdf *.tex
