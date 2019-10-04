# -*- coding: utf-8 -*-

from PyQt5 import QtGui, QtCore, QtWidgets
import pyqtgraph as pg
import numpy as np


class MyPlot(pg.PlotWidget):
    def mousePressEvent(self, event):
        print("MyPlot widget clicked: x=", event.pos().x(), "; y=", event.pos().y())

class MouseFilter(QtCore.QObject):
    def eventFilter(self, obj, ev):
        if(ev.type() == QtCore.QEvent.MouseButtonPress):
            print("Event filter: mouse pressed: x=", event.pos().x(), "; y=", event.pos().y())
            return true
        return false


class MyWindow(QtWidgets.QWidget):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent)

        self.setWindowTitle("pyqtgraph example 1: Simple usage")
        self.vbox = QtWidgets.QVBoxLayout()

        self.plot = MyPlot(self)

        x = np.arange(100)
        y = np.random.normal(size=100)
        self.plot.plot(x, y)

        self.setMouseTracking(True)
        # self.filter = MouseFilter(self.plot)
        # self.plot.installEventFilter(self.plot)

        self.vbox.addWidget(self.plot)
		
        self.setLayout(self.vbox)
        self.setMinimumHeight(800)
        self.setMinimumWidth(1200)


    def mousePressEvent(self, event):
        print("MyWindow clicked")
        event.accept()



if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)

    window = MyWindow()
    window.show()

    sys.exit(app.exec_())