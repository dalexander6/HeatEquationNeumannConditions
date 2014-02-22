SHELL := /bin/bash
PDF_FILES := $(patsubst %.tex, %.pdf,$(wildcard *.tex))

processor=$(unamestr -p)
.SUFFIXES: 
.SUFFIXES: .tex .pdf

all : $(PDF_FILES) 

%.pdf : %.tex
	@echo "----------Making $@ from $< (from .tex.pdf)"	
	rubber --inplace --maxerr -1 --short --force --warn all --pdf $<
	@echo "-------------Done"
	
#if in 11.04, we are using gnome-open
#to raise to forefront is complicated.
#we have to get the parent window id, which is in hex
#and then the frame-id is conjected to be one less than this
#do the subtraction, but it doesn't have a 0x prepended
#prepend the 0x
#run a c++ program totop from totop.cpp
#doesnt' work: xdotool search --name $@ windowraise ;
	@if [[ $$(lsb_release -r | grep 11.04 -c) = "1" ]]; then \
		echo "detected natty" ;\
		gnome-open $@ & \
		fidp1=$$(xwininfo -name "$@" -children | grep "Parent window id:" | awk "{ print \$$4 }") ;\
		fidp1=$$(printf "%x\n" $$[ $$fidp1 - 1 ]) ;\
		fid="0x$$fidp1" ;\
		totop $$fid ;\
	fi
	#evince $@ &; \ 

clean : 
	rm -rf *.log *.aux

