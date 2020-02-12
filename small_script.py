#app.py

import sys 
import numpy as np
import matplotlib.pyplot as plt
#import required packages

if (len (sys.argv) != 2 or int(sys.argv[1]) >6):
  print("Usage:\n      insert command line arguments '1' to get LINEAR function" )  
  print("\n      insert command line arguments '2' to get SIN function" )
  print("\n      insert command line arguments '3' to get COS function" )
  print("\n      insert command line arguments '4' to get TAN function" )
  print("\n      insert command line arguments '5' to get EXPONENTIAL function" )
  print("\n      insert command line arguments '6' to get SQUARE ROOT function of ABSOLUTE VALUE" )
  sys.exit (1)

#if amount of our arguments more then 2 (one of them it is name of our script)

#and if inserted argument not equal to ...
#we get for user list of the supported functions and the corresponding numbers  
#and then exiting our program 

def f(t):

        if int(sys.argv[1]) == 1:
        	return t

        if int(sys.argv[1]) == 2:
                return np.sin(t)

	if int(sys.argv[1]) == 3:
		return np.cos(t)

	if int(sys.argv[1]) == 4:
		return np.tanh(t)
        
	if int(sys.argv[1]) == 5:
                  return np.exp(t)
       
	if int(sys.argv[1]) == 6:
                  return np.sqrt(np.absolute(t))
#here we defined our functions according to instruction. 

eps = 0.01
#we defined step of our list
xval=np.arange(-3, 3, eps)
#filled our xval list by values
yval=f(xval)
#and filled yval list by using of xval and predefined function

plt.plot(xval, yval, 'bo')
#make our plot
plt.title('Small_script')
#name of our plot
plt.xlabel('xval')
plt.ylabel('yval')
#name of our axes
plt.show()
#showing our plot
