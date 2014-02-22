#!/bin/bash
#compiles and runs provided .cpp
#then converts data files to pngs via gnuplot
#then converts pngs to gifs

runApprox=1
runNeumann=0

printf -- "\n\n*************dostuff .sh*************\n"

if [ $runNeumann -eq 1 ]
then 
	./HeatEqn1D.exe
	#only proceed if successfuly completed
	if [ $? != 0 ]
	then
		exit
	fi
fi

if [ $runApprox -eq 1 ]
then
	./HeatEqn1DApprox.exe
	#only proceed if successfuly completed
	if [ $? != 0 ]
	then
		echo "Program failed, aborting dostuff.sh"
		exit
	fi
fi

cd data
ls *.dat | sed "s/.dat//" > list
for i in `cat list` ; do
#echo $i
sed -e "s/OUTFILE/$i/" -e "s/INFILE/$i/" \
../plotter.plt | gnuplot
done
#rm *.dat
rm list


#code to make animated gifs

#move current edition to backup folder
#but only if we actually make a new one! hence the if statement
if [ $runNeumann -eq 1 ]
then
HeatNormalSchemeN
	mv HeatTrueU.gif ./backups/
	convert -delay 20 -loop 0 HeatTrueU* HeatTrueU.gif
	if [ $? != 0 ]
	then
		echo "TrueUU gif creation failed, restoring backup"
		mv ./backups/HeatTrueU.gif ./;
	else
		rm HeatTrueU*.png
	fi

	mv HeatNormalSchemeU.gif ./backups/
	convert -delay 20 -loop 0 HeatNormalSchemeU*.png HeatNormalSchemeU.gif
	if [ $? != 0 ]
	then
		echo "U gif creation failed, restoring backup"
		mv ./backups/HeatNormalSchemeU.gif ./;
	else
		rm HeatNormalSchemeU*.png
	fi
fi

if [ $runApprox -eq 1 ]
then
	mv HeatApproxU.gif ./backups/
	convert -delay 20 -loop 0 HeatApproxU*.png HeatApproxU.gif
	if [ $? != 0 ]
	then
		echo "Approx U gif creation failed, restoring backup"
		mv ./backups/HeatApproxU.gif ./;
	else
		rm HeatApproxU*.png
	fi
fi

#rm *.png

#rm *.dat
printf "*************dostuff.sh COMPLETED******\n\n"
