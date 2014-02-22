#!/usr/bin/env python
# -*- coding: utf-8 -*-
#       Copyright 2011 Damon <damon@damon-desktop>
#       
import execCommand
import os
import math

def main():
	#set base parameters
	xPanelBase = 100
	tPanelBase = 25 
	NBase = 64
	callingScript = "projectRunner.py"

	#Generate all permutations
	

	resultsFile = "data.txt"
	os.remove(resultsFile)
	

	#Start computing
	#for k in range(sweepCountMax+1):
	
	Nlen=13
	panelIters = 7
	for i in range(Nlen):
		N = NBase*2**i
		for j in range(3,panelIters):
			xPanel = xPanelBase * 2**j
			tPanel = tPanelBase * 4**j
		
			command = "./HeatEqn1DApprox.exe " + repr(xPanel) + " " + repr(tPanel) + " " + repr(N) 
			print(command)
	
			execCommand.execCommand(callingScript, command, resultsFile)
	
	return 0

if __name__ == '__main__':
	main()

