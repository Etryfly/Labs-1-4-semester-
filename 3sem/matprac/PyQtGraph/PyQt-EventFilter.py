import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtCore import QObject
import PyQt5.QtCore as QtCore
import PyQt5.QtGui as QtGui


class SomeFilter(QObject):
    def eventFilter(self, obj, ev):
        if ev.type() == QtCore.QEvent.MouseButtonPress:
            if ev.button() == QtCore.Qt.LeftButton:
                print("Event filtering ok")
                return True
        return False


class MainWidget(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)
        self.ev_filter = SomeFilter(self)
        self.installEventFilter(self.ev_filter)


app = QApplication(sys.argv)
w = MainWidget()
w.show()
sys.exit(app.exec_())