#!/usr/bin/env python
# -*- coding: utf-8 -*-
#       Copyright 2011 Damon <damon@damon-desktop>
#       
import execCommand
import os
import math

def f(e1, e2):
	return math.log(e1/e2, 2)

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
	panelIters = 3
	for i in range(Nlen):
		N = NBase*2**i
		for j in range(3,panelIters+3):
			xPanel = xPanelBase * 2**j
			tPanel = tPanelBase * 4**j
		
			command = "./HeatEqn1DApprox.exe " + repr(xPanel) + " " + repr(tPanel) + " " + repr(N) 
			print(command)
	
			execCommand.execCommand(callingScript, command, resultsFile)
	
	#Start processing data to find rate of convergences
	inputs = open("data.txt", "r")
	array = []
	for line in inputs:
		array.append(line)
	inputs.close()
	
	counter = 0
	errors = []
	
	for i in range(len(array)):
		if ((i + 1)%(2*panelIters) == 0):
			errors.append(float(array[i]))
	
	print(errors)

	baseN = 64
	num_errors = len(errors)
	for i in range(1,num_errors):
		p_estimate = f(errors[i-1],errors[i])
		string = "$" + repr(baseN*2**i) + "$ & $" + repr(errors[i]) + "$ & $" + repr(p_estimate) + "$ \\\\"
		#print(p_estimate)
		print(string)

	
	return 0

if __name__ == '__main__':
	main()

