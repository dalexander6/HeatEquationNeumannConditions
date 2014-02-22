import math
#workingDirectory = "/home/damon/scripts/tmp/"


def f(e1, e2):
	return math.log(e1/e2, 2)

def main():
	inputs = open("data.txt", "r")
	array = []
	for line in inputs:
		array.append(line)
	inputs.close()
	
	counter = 0
	errors = []
	
	for i in range(len(array)):
		if ((i + 1)%8 == 0):
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
