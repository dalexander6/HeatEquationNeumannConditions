#!/bin/bash
#compiles and runs provided .cpp
#then converts data files to pngs via gnuplot
#then converts pngs to gifs


runApprox=1
runNeumann=0

printf -- "\n\n*************dostuff .sh*************\n"

if [ $runNeumann -eq 1 ]
then 
	./HeatEqn2D.exe
	#only proceed if successfuly completed
	if [ $? != 0 ]
	then
		exit
	fi
fi

if [ $runApprox -eq 1 ]
then
	./HeatEqn2DApprox.exe
	#only proceed if successfuly completed
	if [ $? != 0 ]
	then
		echo "Program failed, aborting dostuff.sh"
		exit
	fi
fi

cd data


#convert dats to pictures
ls *.dat | sed "s/.dat//" > list
for i in `cat list` ; do
	#echo $i
	sed -e "s/OUTFILE/$i/" -e "s/INFILE/$i/" \
	../plotterTwoCircles.plt | gnuplot
	#../plotter.plt | gnuplot
done
rm *.dat
rm list


printf "\ndone creating data files\n"
#code to make animated gifs

#move current edition to backup folder
#but only if we actually make a new one! hence the if statement
if [ $runNeumann -eq 1 ]
then

	mv Ex3HeatU.gif ./backups/
	convert -delay 20 -loop 0 Ex3HeatU*.png Ex3HeatU.gif
	if [ $? != 0 ]
	then
		echo "U gif creation failed, restoring backup"
		mv ./backups/Ex3HeatU.gif ./;
	else
		rm Ex3HeatU*.png
	fi
fi

if [ $runApprox -eq 1 ]
then
	#mv TrueU.gif ./backups/
	#convert -delay 10 -loop 0 TrueU* TrueU.gif
	#if [ $? != 0 ]
	#then
	#	echo "TrueU gif creation failed, restoring backup"
	#	mv ./backups/TrueU.gif ./;
	#else
	#	rm TrueU*.png
	#fi
	mv HeatApproxU.gif ./backups/
	convert -delay 10 -loop 0 HeatApproxU*.png HeatApproxU.gif
	if [ $? != 0 ]
	then
		echo "Approx U gif creation failed, restoring backup"
		mv ./backups/HeatApproxU.gif ./;
	else
		rm HeatApproxU*.png
	fi

	#convert -delay 10 -loop 0 deltaU*.png deltaU.gif
	#rm deltaU*.png
fi

#rm *.png

printf "*************dostuff.sh COMPLETED******\n\n"
