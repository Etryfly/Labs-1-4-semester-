# -*- coding: utf-8 -*-
"""
This example demonstrates many of the 2D plotting capabilities
in pyqtgraph. All of the plots may be panned/scaled by dragging with 
the left/right mouse buttons. Right click on any plot to show a context menu.
"""
import math
from cmath import cos, sin, sin

from pyqtgraph.Qt import QtGui, QtCore
import numpy as np
import pyqtgraph as pg


#QtGui.QApplication.setGraphicsSystem('raster')
app = QtGui.QApplication([])
#mw = QtGui.QMainWindow()
#mw.resize(800,800)

win = pg.GraphicsWindow(title="Basic plotting examples")
win.resize(1000,600)
win.setWindowTitle('pyqtgraph example: Plotting')

# Enable antialiasing for prettier plots
pg.setConfigOptions(antialias=True)

p6 = win.addPlot(title="Updating plot")
curve = p6.plot(pen='y')
# data = np.random.normal(size=(10,1000))


r = 5
arr = np.ndarray((360, 2))
for i in np.arange(360):
    arr[i] = [r * np.math.cos(i * math.pi / 180), r * math.sin(i * math.pi / 180)]


ptr = 0
# data = np.row_stack(arrx, arry)
def update():
    global curve, data, ptr, p6, arrx, arry
    curve.setData(arr[:ptr])
    if ptr == 0:
        p6.enableAutoRange('xy', False)  ## stop auto-scaling after the first data set is plotted
    ptr += 1
timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(30)


## Start Qt event loop unless running in interactive mode or using pyside.
if __name__ == '__main__':
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()
