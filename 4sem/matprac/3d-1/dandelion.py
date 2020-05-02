from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph as pg
import pyqtgraph.opengl as gl
import numpy as np
import sys
import math


"""
Simple examples demonstrating the use of GLMeshItem.

"""

QtCore.QCoreApplication.setAttribute(QtCore.Qt.AA_UseDesktopOpenGL)
app = QtGui.QApplication([])

w = gl.GLViewWidget()
w.show()
w.setWindowTitle('pyqtgraph example: GLMeshItem')
w.setCameraPosition(distance=40)

g = gl.GLGridItem()
g.scale(2, 2, 1)
w.addItem(g)


R = 10
r=10


phi_rng = np.linspace(0, 2*math.pi, 15)
theta_rng = np.linspace(0, math.pi, 15)

for phi in phi_rng:
    for theta in theta_rng:
        x = r * math.sin(theta) * math.cos(phi)
        y = r * math.sin(theta) * math.sin(phi)
        z = r * math.cos(theta)
        d = 0.5
        x2 = (r + d) * math.sin(theta) * math.cos(phi)
        y2 = (r + d) * math.sin(theta) * math.sin(phi)
        z2 = (r + d) * math.cos(theta)
        pts = np.array([[x, y, z], [x2, y2, z2]])
        ptss = np.array([[x, y, z], [0, 0, 0]])
        plt = gl.GLLinePlotItem(pos=pts, width = 4, color=pg.glColor(200, 200, 0))
        pltt = gl.GLLinePlotItem(pos=ptss, color=pg.glColor(255, 255, 255))
        w.addItem(plt)
        w.addItem(pltt)





sys.exit(app.exec_())  # Запускаем цикл обработки событий
