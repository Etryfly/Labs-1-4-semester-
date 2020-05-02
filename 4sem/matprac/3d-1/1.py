from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph as pg
import pyqtgraph.opengl as gl
import numpy as np
import sys


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



# verts = np.array([
#     [0, 0, 0],
#     [2, 0, 0],
#     [1, 2, 0],
#     [1, 1, 1],
# ])
faces = np.array([
    [0, 1, 2],
    [0, 1, 3],
    [0, 2, 3],
    [1, 2, 3]
])
colors = np.array([
    [1, 0, 0, 0.3],
    [0, 1, 0, 0.3],
    [0, 0, 1, 0.3],
    [1, 1, 0, 0.3]
])


a=2
b=3
verts = np.empty((69, 3, 3), dtype=np.float32)
theta = np.linspace(0, 5*np.pi, 70)[:-1]
verts[:,0] = np.vstack([a*np.cos(theta), a*np.sin(theta), b*theta]).T
verts[:,1] = np.vstack([a*np.cos(theta+0.3)*3, a*np.sin(theta+0.2)*3, b*theta]).T
verts[:,2] = np.vstack([a*np.cos(theta-0.2)*5, a*np.sin(theta-0.2)*5, b*theta]).T


## Colors are specified per-vertex
colors = np.random.random(size=(verts.shape[0], 3, 4))
m2 = gl.GLMeshItem(vertexes=verts, vertexColors=colors, smooth=False, shader='balloon',
                   drawEdges=True, edgeColor=(1, 1, 0, 1))
m2.translate(10, 5, 0)
w.addItem(m2)




a=2
b=1
verts = np.empty((500, 3, 3), dtype=np.float32)
theta = np.linspace(0, 5*np.pi, 501)[:-1]
verts[:,0] = np.vstack([a*np.cos(theta), a*np.sin(theta), b*theta]).T
verts[:,1] = np.vstack([a*np.cos(theta), a*np.sin(theta), b*theta]).T
verts[:,2] = np.vstack([a*1.1*np.cos(theta), a*np.sin(theta), b*theta]).T




## Colors are specified per-vertex
colors = np.random.random(size=(verts.shape[0], 3, 4))
m3 = gl.GLLinePlotItem(pos=verts, color=(1, 1, 1, 1), width=3, antialias=True)
m3.translate(-5, 5, 0)
w.addItem(m3)

a=2
b=1
verts = np.empty((500, 3, 3), dtype=np.float32)
theta = np.linspace(5*np.pi, 10*np.pi, 501)[:-1]
verts[:,0] = np.vstack([a*np.cos(theta), a*np.sin(theta), b*(theta -5*np.pi) ]).T
verts[:,1] = np.vstack([a*np.cos(theta), a*np.sin(theta), b*(theta -5*np.pi)]).T
verts[:,2] = np.vstack([a*1.1*np.cos(theta), a*np.sin(theta), b*(theta -5*np.pi)]).T

colors = np.random.random(size=(verts.shape[0], 3, 4))
m4 = gl.GLLinePlotItem(pos=verts, color=(1, 1, 0, 1), width=3, antialias=True)

m4.translate(-5, 5, 0)
w.addItem(m4)

a=np.pi/3
r=5
l = 4
verts = np.empty((500, 3, 3), dtype=np.float32)
theta = np.linspace(-10*np.pi, 10*np.pi, 501)[:-1]
verts[:,0] = np.vstack([r*np.cos(theta) / np.cosh((theta-l)*(np.cos(a) / np.sin(a))),
                        r*np.sin(theta) / np.cosh((theta - l)*(np.cos(a) / np.sin(a))),
                        r*np.tanh((theta - l) *(np.cos(a) / np.sin(a))) ]).T
verts[:,1] = np.vstack([r*np.cos(theta) / np.cosh((theta-l)*(np.cos(a) / np.sin(a))),
                        r*np.sin(theta) / np.cosh((theta - l)*(np.cos(a) / np.sin(a))),
                        r*np.tanh((theta - l) *(np.cos(a) / np.sin(a))) ]).T
verts[:,2] = np.vstack([r*1.1*np.cos(theta) / np.cosh((theta-l)*(np.cos(a) / np.sin(a))),
                        r*np.sin(theta) / np.cosh((theta - l)*(np.cos(a) / np.sin(a))),
                        r*np.tanh((theta - l) *(np.cos(a) / np.sin(a))) ]).T

colors = np.random.random(size=(verts.shape[0], 3, 4))

pts = np.array(verts)
m5 = gl.GLLinePlotItem(pos=pts, color=(1, 1, 1, 1), width=3, antialias=True)
w.addItem(m5)


sys.exit(app.exec_())  # Запускаем цикл обработки событий
