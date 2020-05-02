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


phi_rng = np.linspace(0, 2*math.pi, 6)
theta_rng = np.linspace(0, math.pi, 6)

for phi in phi_rng:
    for theta in theta_rng:
        x = r * math.sin(theta) * math.cos(phi)
        y = r * math.sin(theta) * math.sin(phi)
        z = r * math.cos(theta)
        d = 5
        x2 = (r + d) * math.sin(theta) * math.cos(phi)
        y2 = (r) * math.sin(theta) * math.sin(phi)
        z2 = (d) * math.cos(theta)


        verts = np.empty((69, 3, 3), dtype=np.float32)
        theta = np.linspace(0, 5 * np.pi, 70)[:-1]
        verts[:, 0] = np.vstack([x,y,z]).T
        verts[:, 1] = np.vstack([x2,y2,z2]).T
        verts[:, 2] = np.vstack([0,0,0]).T


        # ptss = np.array([[x, y, z], [0, 0, 0]])
        colors = np.random.random(size=(verts.shape[0], 3, 4))
        plt = gl.GLMeshItem(vertexes=verts, vertexColors=colors, smooth=False, shader='balloon',
                   drawEdges=True, edgeColor=(1, 1, 0, 1))
        w.addItem(plt)






sys.exit(app.exec_())  # Запускаем цикл обработки событий
