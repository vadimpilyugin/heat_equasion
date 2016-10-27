#! /usr/bin/python

import matplotlib.pyplot as plt
import numpy as np
import pylab
from scipy.interpolate import spline
import ConfigParser
import StringIO
import sys

with open("config.cfg", 'r') as f:
    config_string = '[section]\n' + f.read()
config = ConfigParser.ConfigParser()
buf = StringIO.StringIO(config_string)
config.readfp(buf)
x_left = config.getfloat('section', 'x_left')
x_right = config.getfloat('section', 'x_right')
x_steps = config.getfloat('section', 'x_steps')

lines = open(sys.argv[1], 'r').readlines()

x = np.linspace(x_left,x_right,x_steps)
#xnew = np.linspace(x_left,x_right,x_steps+50)
y = np.array([float(p) for p in lines[0].split(' ')[0:-1]])

# You probably won't need this if you're embedding things in a tkinter plot...
plt.ion()

fig = plt.figure()
ax = fig.add_subplot(111)
line1, = ax.plot(x, y, 'r-') # Returns a tuple of line objects, thus the comma

for line in lines:
	y = np.array([float(p) for p in line.split(' ')[0:-1]])
	line1.set_ydata(spline(x,y,x))
	pylab.axis([x_left,x_right,-20,20])
	fig.canvas.draw()
plt.close()
