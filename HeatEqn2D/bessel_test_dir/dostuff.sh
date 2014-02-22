#!/bin/bash
#compiles and runs provided .cpp
#then converts data files to pngs via gnuplot
#then converts pngs to gifs


printf -- "\n\n*************dostuff .sh*************\n"

pwd
./bessel_test.exe

cd data
ls *.dat | sed "s/.dat//" > list
for i in `cat list` ; do
echo $i
sed -e "s/OUTFILE/$i/" -e "s/INFILE/$i/" \
../plotter.plt | gnuplot
done
#rm *.dat
rm list

printf "*************dostuff.sh COMPLETED******\n\n"
