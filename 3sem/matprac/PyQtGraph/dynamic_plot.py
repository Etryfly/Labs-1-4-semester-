# -*- coding: utf-8 -*-
"""
This example demonstrates many of the 2D plotting capabilities
IN pyqtgraph. All of the plots may be panned/scaled by dragging with
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
# p7 = win.addPlot(title="Updating plot")
curve = p6.plot(pen='r')
# curve1 = p7.plot(pen='y')
# data = np.random.normal(size=(10,1000))


r = 20
# arrC = np.ndarray((360, 2))
arr = []
for i in range(-10, 11):
    x = i
    y = x ** 2
    arr.append([x,y,0])

arr = np.array(arr)
# arr = np.add(arr, [[0, r, 0]])



    # arrC[i] = [r*math.cos(((i - 180) * math.pi) / 180), r*math.sin(((i - 180) * math.pi) / 180)]
    # arr[i] = np.dot(arr[i], rot_mat_z)
alpha = 1
ptr = 0
# data = np.row_stack(arrx, arry)
def update():
    global curve, data, ptr, p6, arrx, arry, arr, alpha

    alpha += 1
    a = (alpha * math.pi) / 180
    rot_mat_z = [
        [math.cos(a), math.sin(a), 0],
        [-math.sin(a), math.cos(a), 0],
        [0, 0, 1]
    ]

    rot_mat_a = [
        [math.cos(a),  0, math.sin(a)],
        [0, 1, 0],
        [-math.sin(a), 0 , math.cos(a)]
    ]

    rot_mat_z = np.array(rot_mat_z)
    rot_mat_a = np.array(rot_mat_a)
    data = arr.copy()
    data = np.add(data, [[0, 10, 0]])
    data = np.dot(data, rot_mat_a)
    data = np.dot(data, rot_mat_z)

    curve.setData(data[:, 0:2])
    # curve1.setData(arrC[:ptr])
    if ptr == 0:
        p6.enableAutoRange('xy', False)  ## stop auto-scaling after the first data set is plotted
    ptr += 1
timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(30)


## Start Qt event loop unless running IN interactive mode or using pyside.
if __name__ == '__main__':
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()
