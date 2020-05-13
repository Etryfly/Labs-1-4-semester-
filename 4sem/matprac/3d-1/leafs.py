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

verts = []

phi_rng = np.linspace(0, 2*math.pi, 15)
theta_rng = np.linspace(0, math.pi, 15)

verts.append([0, 0, 0])
for theta in theta_rng:
    for phi in phi_rng:
        x = R * math.sin(theta) * math.cos(phi)
        y = R * math.sin(theta) * math.sin(phi)
        z = R * math.cos(theta)
        verts.append([x, y, z])

i = 1
flag = 1
for theta in theta_rng:
    if flag:
        flag = 0
    else:
        flag = 1
    j = flag

    for phi in phi_rng:
        if (j % 2 == 0) and (j > 1):
            mi = gl.GLMeshItem(vertexes=np.array([verts[0].copy(), verts[i - 1].copy(), verts[i].copy()])
                               , faces=np.array([[0, 1, 2]])
                               , smooth=False
                               , drawEdges=True
                               , color=(0, 1, 0, 1)
                               , computeNormals=True)
            w.addItem(mi)
        i += 1
        j += 1







sys.exit(app.exec_())  # Запускаем цикл обработки событий
