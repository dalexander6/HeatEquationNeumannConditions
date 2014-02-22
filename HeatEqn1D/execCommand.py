import subprocess

def execCommand(callingScript,command,resultsFile = None,verboseFlag = False):
#
# If no results file is specified, then the calling script executes the command
# and standard input and output are connected to the console. The results are
# APPENDED to the specified resultsFile
#
	if(resultsFile == None):
		p = subprocess.Popen(command,shell=True,stdout=None,stderr=None)
		p.wait()
		if((p.returncode != None) and (p.returncode != 0)):
			className = callingScript.__class__.__name__
			print '\n======== ' + className + ' Error ========='
			print 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX '
			print 'XXXXXXX Execution Halted XXXXXXXXXXXXX '
			print 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX '
			sys.exit(1)
		return

#
# If a results file is specified, then the calling script executes the command
# and standard input and output are captured and written to the results file
#
	p = subprocess.Popen(command,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
	(runOutput,runError)  = p.communicate()
# Using communicate fixed a buffer problem --- the code below was the original that stopped working.
#(r,e) = (p.stdout, p.stderr)
#runOutput = r.read();
#runError  = e.read();
#r.close()
#e.close()

	if((p.returncode != None) and (p.returncode != 0)):
		className = callingScript.__class__.__name__
		print '\n======== ' + className + ' Error ========='
		print 'Command : '
		print  command
		print '\nOutput : '
		print runOutput
		print runError

		if(resultsFile != None):
			'''
			if os.sys.platform == 'win32':
				outputFile = runOutput.replace("\r\n", "\n")
				f = open(resultsFile, "ab+")
				f.write(outputFile)
				f.close()
			else:
			'''
			f = open(resultsFile, "ab+")
			f.write(runOutput)
			f.close()
			'''
			if os.sys.platform == 'win32':
				outputFile = runError.replace("\r\n", "\n")
				f = open(resultsFile, "ab+")
				f.write(outputFile)
				f.close()
			else:
			'''
			f = open(resultsFile, "ab+")
			f.write(runError)
			f.close()

			print 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX '
			print 'XXXXXXX Execution Halted XXXXXXXXXXXXX '
			print 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX '
			sys.exit(1)


	if(verboseFlag) : print runOutput

	if(resultsFile != None):
		'''
		if os.sys.platform == 'win32':
			outputFile = runOutput.replace("\r\n", "\n")
			f = open(resultsFile, "ab+")
			f.write(outputFile)
			f.close()
		else:
		'''
		f = open(resultsFile, "ab+")
		f.write(runOutput)
		f.close()


	if(runOutput.find("executable not specified") != -1):
		print "XXXX Program Halted XXXX"
		sys.exit(1);
	return
	
