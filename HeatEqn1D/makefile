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
CFLAGS  = -g -Wall -O3
CDIR = ../common_files/
INCLUDES = -I ../common_files
SOURCES = GridFun1D.cpp TriSolver.cpp CrankNicolsonOp1D.cpp CrankNicolsonApproxOp1D.cpp toolboxFunctions.cpp GridFun2D.cpp
HEADERS = $(SOURCES:.cpp=.h)
HEADERS += outputToGNUplot.h GridParameters.h PaddedGridParameters.h 
HEADERS += GridOutput.h
OBJECTS = $(SOURCES:.cpp=.o)
MAINS = HeatEqn1D.cpp HeatEqn1DApprox.cpp
EXECUTABLES = $(MAINS:.cpp=.exe)
vpath %.cpp $(CDIR)
vpath %.h $(CDIR)

.SUFFIXES: 
.SUFFIXES: .tex .pdf .cpp .o .h


all : PHONY $(PDF_FILES) $(EXECUTABLES) $(HEADERS)
	@printf -- "--------------MAKE COMPLETED--------------\n\n"

HeatEqn1D.exe: HeatEqn1D.cpp $(OBJECTS) $(HEADERS)
	@echo "----------Making HeatEqn1D.exe------------------------------"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $< -o $@
	@echo "----------Done----------------------------------------"

HeatEqn1DApprox.exe: HeatEqn1DApprox.cpp $(OBJECTS) $(HEADERS)
	@echo "----------Making HeatEqn1DApprox.exe------------------------------"
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




