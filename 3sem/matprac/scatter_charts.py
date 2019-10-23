# -*- coding: utf-8 -*-
"""
This example shows all the scatter plot symbols available IN pyqtgraph.

These symbols are used to mark point locations for scatter plots and some line
plots, similar to "markers" IN matplotlib and vispy.
"""
from math import sin
import numpy as np
from numpy.ma import arange, cos
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg

app = QtGui.QApplication([])
win = pg.GraphicsWindow(title="Scatter Plot Symbols")
win.resize(1000,600)

pg.setConfigOptions(antialias=True)

plot = win.addPlot(title="Plotting with symbols")
plot.addLegend()
r = 5
arrx = []
arry = []

for i in arange(1, 50, 0.001):
    arrx.append(r*cos(i))
    arry.append(r*sin(i))

plot.plot(arrx, arry, pen=(0, 200, 0), symbolBrush=(255, 255, 0), symbolPen='r', symbol='o',
              symbolSize=14, name="symbol='o'")

# plot.plot([1, 2, 3, 4, 5], pen=(0,128,0), symbolBrush=(0,128,0), symbolPen='w', symbol='t', symbolSize=14, name="symbol='t'")
# plot.plot([2, 3, 4, 5, 6], pen=(19,234,201), symbolBrush=(19,234,201), symbolPen='w', symbol='t1', symbolSize=14, name="symbol='t1'")
# plot.plot([3, 4, 5, 6, 7], pen=(195,46,212), symbolBrush=(195,46,212), symbolPen='w', symbol='t2', symbolSize=14, name="symbol='t2'")
# plot.plot([4, 5, 6, 7, 8], 200pen=(250,194,5), symbolBrush=(250,194,5), symbolPen='w', symbol='t3', symbolSize=14, name="symbol='t3'")
# plot.plot([5, 6, 7, 8, 9], pen=(54,55,55), symbolBrush=(55,55,55), symbolPen='w', symbol='s', symbolSize=14, name="symbol='s'")
# plot.plot([6, 7, 8, 9, 10], pen=(0,114,189), symbolBrush=(0,114,189), symbolPen='w', symbol='p', symbolSize=14, name="symbol='p'")
# plot.plot([7, 8, 9, 10, 11], pen=(217,83,25), symbolBrush=(217,83,25), symbolPen='w', symbol='h', symbolSize=14, name="symbol='h'")
# plot.plot([8, 9, 10, 11, 12], pen=(237,177,32), symbolBrush=(237,177,32), symbolPen='w', symbol='star', symbolSize=14, name="symbol='star'")
# plot.plot([9, 10, 11, 12, 13], pen=(126,47,142), symbolBrush=(126,47,142), symbolPen='w', symbol='+', symbolSize=14, name="symbol='+'")
# plot.plot([10, 11, 12, 13, 14], pen=(119,172,48), symbolBrush=(119,172,48), symbolPen='w', symbol='d', symbolSize=14, name="symbol='d'")
plot.setXRange(-2, 4)
plot.setYRange(-2, 2)

## Start Qt event loop unless running IN interactive mode or using pyside.
if __name__ == '__main__':
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()
