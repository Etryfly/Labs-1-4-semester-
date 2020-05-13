from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph.opengl as gl
import pyqtgraph as pg
import numpy as np
import math


def draw(_R, _w):
    b = _R/15
    t_rng = np.linspace(0, 4*math.pi, 180)
    arr_spiral = []
    for t in t_rng:
        x = _R*math.cos(t)
        y = _R*math.sin(t)
        z = b*t

        x1 = _R * math.cos(t + 0.1)
        y1 = _R * math.sin(t + 0.1)
        z1 = b * t
        arr_spiral.append([x, y, z])

        verts = np.array([
            [0, 0, z],
            [x, y, z],
            [x1, y1, z1]
        ])

        plt = gl.GLMeshItem(vertexes=verts
                               , faces=np.array([[0, 1, 2]])
                               , smooth=False
                               , drawEdges=True
                               , color=(1, 1, 0, 1)
                               , computeNormals=True)
        _w.addItem(plt)

    plt = gl.GLLinePlotItem(pos=np.array(arr_spiral), color=pg.glColor(200, 200, 0))
    _w.addItem(plt)


if __name__ == '__main__':
    import sys

    # строка для ОС Windows, чтобы для отрисовки треугольников использовался
    # тоже OpenGL
    # т.е. чтобы не сваливался в черный экран с исключениями
    QtCore.QCoreApplication.setAttribute(QtCore.Qt.AA_UseDesktopOpenGL)

    app = QtGui.QApplication([])

    w = gl.GLViewWidget()
    w.opts['distance'] = 40
    w.show()
    w.setWindowTitle('pyqtgraph example: Спираль')

    # Grid mesh
    gx = gl.GLGridItem()
    gx.rotate(90, 0, 1, 0)
    gx.translate(-10, 0, 0)
    w.addItem(gx)
    gy = gl.GLGridItem()
    gy.rotate(90, 1, 0, 0)
    gy.translate(0, -10, 0)
    w.addItem(gy)
    gz = gl.GLGridItem()
    gz.translate(0, 0, -10)
    w.addItem(gz)

    # AXIS
    size = QtGui.QVector3D(10, 10, 10)
    axis = gl.GLAxisItem(size, antialias=False)
    # z - green
    # y - yellow
    # x - blue
    w.addItem(axis)

    draw(_w=w, _R=10)

    sys.exit(app.exec_())
