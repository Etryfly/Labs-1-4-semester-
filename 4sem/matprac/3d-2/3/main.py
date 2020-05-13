from PyQt5 import QtCore, QtWidgets, QtGui
import pyqtgraph as pg
import numpy as np
import math
import sys


class GPS_Widget(QtWidgets.QMainWindow):
    # signal_to_baud_rate_change = QtCore.pyqtSignal(int)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("ДЗ №3")

        # стандартная разметка для QWidget
        main_widget = QtWidgets.QWidget()
        lay = QtWidgets.QHBoxLayout()
        main_widget.setLayout(lay)
        self.setCentralWidget(main_widget)
        self.setMinimumSize(800, 600)

        # Холст с графиками (2D pyqtgraph)
        pg_view = pg.GraphicsView()
        pg_canvas = pg.PlotItem()
        pg_view.setCentralWidget(pg_canvas)
        self.__nav_canvas_vb = pg_canvas.vb
        self.__nav_canvas = pg_canvas
        self.__nav_canvas_view = pg_view
        lay.addWidget(pg_view)

        vlay = QtWidgets.QVBoxLayout()
        lay.addLayout(vlay)

        self.__init_plots()

        self.__mapper = QtCore.QSignalMapper(self)
        for i in range(0, len(self.__plots_data_list)):
            bttn1 = QtWidgets.QPushButton("Кнопка {}".format(i))
            vlay.addWidget(bttn1)
            bttn1.clicked.connect(self.__mapper.map)
            self.__mapper.setMapping(bttn1, i)

        self.__mapper.mapped['int'].connect(self.__bttn_clicked)

        self.__frame_curr_i = 0
        self.__plot_curr_i = 0

        self.__timer_id = self.startTimer(50)
        if self.__timer_id == -1:
            print("Не смог создать таймер - анимации больше не будет")

    def __init_plots(self):
        brush = QtGui.QBrush(QtGui.QColor(250, 0, 0, 250))
        print("brush = ", brush)
        xy = []
        self.__frames_quo_max = 1000
        r = 5
        for i in range(0, self.__frames_quo_max):
            t = math.radians(i)
            xy.append([r*t-r*math.sin(t), r - r*math.cos(t)])
        xy = np.array(xy)
        curve = pg.PlotDataItem(xy, pen='y')
        self.__nav_canvas.addItem(item=curve)
        plots_data_list = []
        plots_data_list.append(xy)

        xy = []
        for i in range(0, self.__frames_quo_max):
            xy.append([i, math.cos(math.radians(i))])
        xy = np.array(xy)
        plots_data_list.append(xy)

        self.__plots_data_list = plots_data_list

        self.__plot = curve

    def timerEvent(self, event):
        self.__frame_curr_i += 2
        self.__frame_curr_i %= self.__frames_quo_max
        print("timerEvent: {}".format(self.__frame_curr_i))
        self.__plot.setData(self.__plots_data_list[self.__plot_curr_i][:self.__frame_curr_i])

    @QtCore.pyqtSlot(int)
    def __bttn_clicked(self, _i):
        print("нажата кнопка {}".format(_i))
        self.__frame_curr_i = 0
        self.__plot_curr_i = _i


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = GPS_Widget()   # Создаем экземпляр класса
    window.setWindowTitle("Загрузка вх. данных и обработка")
    window.show()         # Отображаем окно
    sys.exit(app.exec_()) # Запускаем цикл обработки событий