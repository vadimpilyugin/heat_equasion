#!/usr/bin/python

import sys
import pylab
import numpy
import time
import ConfigParser
import StringIO

with open("config.cfg", 'r') as f:
    config_string = '[section]\n' + f.read()
config = ConfigParser.ConfigParser()
buf = StringIO.StringIO(config_string)
config = ConfigParser.ConfigParser()
config.readfp(buf)
x_left = config.getfloat('section', 'x_left')
x_right = config.getfloat('section', 'x_right')
x_steps = config.getfloat('section', 'x_steps')

pylab.ion()
pylab.xlim([x_left,x_right])
pylab.ylim([0,20])
lines = open(sys.argv[1], 'r').readlines()
for line in lines:
	parts = line.split(' ')
	x_array = numpy.linspace(x_left,x_right,x_steps)
	y_array = parts[0:-1]
	pylab.clf()
	pylab.plot(x_array, y_array)
	pylab.draw()
	time.sleep(0.0001)
pylab.close()
	

