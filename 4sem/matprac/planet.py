from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph.opengl as gl
import pyqtgraph as pg
import numpy as np
import math

app = QtGui.QApplication([])

w = gl.GLViewWidget()

w.showMaximized()
w.show()
w.setWindowTitle('pyqtgraph example: GLLinePlotItem')


t_rng= np.linspace(0, 2*math.pi, 360, endpoint=True)
pts_ellipse = []
for t in t_rng:
    x = 20*math.cos(t)
    y = 10*math.sin(t)
    z = 0

    pts_ellipse.append([x,y,z])

plt_ellipse = gl.GLLinePlotItem(pos=pts_ellipse, color=(1., 1., 1., 1.0), width=3)
pts = np.array([[0., 0., 0.],
                        [0. + 10, 0., 0.]])

pts2 = np.array([0., 0., 0.])
earthPlt = np.array([1., 1., 0.])
plt = gl.GLLinePlotItem(pos=pts,
                        color=(0., 0., 1., 1.0),
                        width=3)


plt2 = gl.GLScatterPlotItem(pos=pts2, size=200, color=(1., 1., 0., 1.0))
earth = gl.GLScatterPlotItem(pos=earthPlt, size=80, color=(0., 1., 0., 1.0))

w.addItem(plt)
w.addItem(plt2)
w.addItem(earth)
w.addItem(plt_ellipse)
_size = 10
w.opts['distance'] = _size
gz = gl.GLGridItem()
gz.setSize(_size, _size, 1)
gz.setSpacing(_size/10, _size/10, _size/10)
w.addItem(gz)

size = QtGui.QVector3D(_size, _size, _size)
axis = gl.GLAxisItem(size, antialias=True)
w.addItem(axis)


if __name__ == '__main__':
    import sys

    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()