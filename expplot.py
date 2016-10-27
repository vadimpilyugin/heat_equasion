#! /usr/bin/python

import matplotlib.pyplot as plt
import numpy as np
import pylab
from scipy.interpolate import spline
import ConfigParser
import StringIO
import sys
import time

with open("config.cfg", 'r') as f:
    config_string = '[section]\n' + f.read()
config = ConfigParser.ConfigParser()
buf = StringIO.StringIO(config_string)
config.readfp(buf)
x_left = config.getfloat('section', 'x_left')
x_right = config.getfloat('section', 'x_right')
x_steps = config.getfloat('section', 'x_steps')

f = open(sys.argv[1], 'r')
line = f.readline()

x = np.linspace(x_left,x_right,x_steps)
xnew = np.linspace(x_left,x_right,x_steps+50)
y = np.array([float(p) for p in line.split(' ')[0:-1]])
ynew = spline(x,y,xnew)

plt.ion()

fig = plt.figure()
ax = fig.add_subplot(111)
line1, = ax.plot(xnew, ynew, 'r-') # Returns a tuple of line objects, thus the comma

while 1:
    where = f.tell()
    line = f.readline()
    if not line:
        time.sleep(1)
        f.seek(where)
    else:
		y = np.array([float(p) for p in line.split(' ')[0:-1]])
		line1.set_ydata(spline(x,y,xnew))
		pylab.axis([x_left,x_right,-20,20])
		fig.canvas.draw()
plt.close()
