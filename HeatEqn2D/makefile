#
# Typing 'make' will create the executable file.
#
# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
PDF_FILES := $(patsubst %.tex, %.pdf,$(wildcard *.tex))
CC = g++
#CFLAGS  = -g -Wall 
CFLAGS  = -O3 -Wall 
CDIR = ../common_files/
INCLUDES = -I ../common_files
SOURCES = GridFun2D.cpp TriSolver.cpp CrankNicolsonApproxOp2D.cpp toolboxFunctions2D.cpp GridFun1D.cpp Point2D.cpp
HEADERS = $(SOURCES:.cpp=.h)
HEADERS += GridParameters2D.h PaddedGridParameters2D.h 
HEADERS += Region.h BoxRegion.h DoubleArray2D.h
HEADERS += GridOutput.h
HEADERS += makefile
OBJECTS = $(SOURCES:.cpp=.o)
MAINS = HeatEqn2DApprox.cpp
EXECUTABLES = $(MAINS:.cpp=.exe)
vpath %.cpp $(CDIR)
vpath %.h $(CDIR)

.SUFFIXES: 
.SUFFIXES: .tex .pdf .cpp .o .h


all : PHONY $(PDF_FILES) $(EXECUTABLES) $(HEADERS)
	cd notes && $(MAKE)
	@printf -- "--------------MAKE COMPLETED--------------\n\n"

HeatEqn2DApprox.exe: HeatEqn2DApprox.cpp $(OBJECTS) $(HEADERS)
	@echo "----------Making HeatEqn2DApprox.exe------------------------------"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $< -o $@
	@echo "----------Done----------------------------------------"

%.pdf : %.tex
	@echo "----------Making $@ from $< (from .tex.pdf)--------------------"	
	rubber --inplace --maxerr -1 --short --force --warn all --pdf $<
	@echo "-------------Done----------------------------------------"
	gnome-open $@ &

%.o : %.cpp %.h
	@echo "----------Making $@ from $< (from .cpp.o)--------------------"	
	$(CC) -c $(CFLAGS) $(INCLUDES) $<
	@echo "-------------Done----------------------------------------"

#Intro message
PHONY: 
	@printf "\n\n**************STARTING MAKE*************\n"
	@echo In: `pwd`

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean:
	rm -f *.exe *.o *~
	rm -rf *.log *.aux




