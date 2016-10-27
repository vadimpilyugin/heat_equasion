#! /usr/bin/python
import pylab
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import spline
import time
import ConfigParser
import StringIO
import sys

print "Hello!"
with open("config.cfg", 'r') as f:
    config_string = '[section]\n' + f.read()
config = ConfigParser.ConfigParser()
buf = StringIO.StringIO(config_string)
config.readfp(buf)
x_left = config.getfloat('section', 'x_left')
x_right = config.getfloat('section', 'x_right')
x_steps = config.getfloat('section', 'x_steps')

pylab.ion()
x_array = np.linspace(x_left,x_right,x_steps)
lines = open(sys.argv[1], 'r').readlines()
for line in lines:
	func_val = line.split(' ')
	y_array = [float(x) for x in func_val[0:-1]]
	pylab.clf()
	pylab.xlim([x_left,x_right])
	pylab.ylim([-20,20])
	
	T = np.array(x_array)
	power = np.array(y_array)
	xnew = np.linspace(x_left,x_right,300)
	power_smooth = spline(T,power,xnew)
	pylab.plot(xnew,power_smooth)
	pylab.draw()
pylab.close()
