Для работы нужен сам пакет pyqtgraph + PyQt5 + numphy
Все устанавливается через pip install

http://www.pyqtgraph.org/documentation/
http://www.pyqtgraph.org/documentation/apireference.html
	
	
	>>> http://www.pyqtgraph.org/documentation/plotting.html
	
	
0.См. 
{|/О графических контейнерах
	http://www.pyqtgraph.org/documentation/plotting.html
	
	Qt:
		QGraphicsView + QGraphicsScene/*model*/
			-> QGraphicsItems /*отдельные объекты*/
	
	{|/Создание графика
		pyqtgraph.plot()	
			- новое окно с графиком
				возвращает PlotWindow (окно с PlotWidget внутри)
		PlotWidget.plot()	
			- добавить новый график(PlotItem) на холст PlotWidget
		PlotItem.plot()	
			- новый график(PlotDataItem) в существующий widget холста графика
		GraphicsLayout.addPlot()	
			- новый график в новую ячейку GridLayout
	}
	
	{|/Уровень QGraphicsItem
		//классы pyqtgraph, пронаследованные от QGraphicsItem
		//должны содержаться в объектах уровня View
		
		|/Полный список
			http://www.pyqtgraph.org/documentation/graphicsItems/index.html
			http://www.pyqtgraph.org/documentation/graphicsItems/plotitem.html
			
		|/Представляют данные
			-> PlotCurveItem
				- линия на графике
			-> ScatterPlotItem
				- маркеры
			-> PlotDataItem 
				- комбинация из ScatterPlotItem и PlotCurveItem

		|/Контейнеры для других QGraphicsItem объектов 
			//-- должны представляться через GraphicsView
			-> PlotItem 
				- содержит ViewBox для отображения данных: график, оси координат, подписей к ним и т.д.
			-> GraphicsLayout 
				- реализует GridLayout
			-> ViewBox 
				- для отображения данных
					встроенное масштабирование содержимого
			-> AxisItem 
				- отображение осей координат: подписей, делений и т.д.
	}
	
	{|/Уровень View 
		//объекты этого уровня можно напрямую добавлять в виджеты PyQt
		-> PlotWidget 
			- пронаследован от GraphicsView 
				отображает одиночный холст графика (PlotItem)
				большинство методов PlotItem доступны и через PlotWidget
		-> GraphicsLayoutWidget 
			- пронаследован от QWidget
				отображает одиночный GraphicsLayoutItem
				, т.е. служит менеджером размещения холстов графиков и пр. объектов уровня GraphicsItem
				--например, распределение разных графиков в разных частях холста
				большинство методов GraphicsLayoutItem доступны и через GraphicsLayoutWidget
	}
}

1.Decoration
	+ несколько графиков на одном полотне
	+ маркеры
	+ кисти и перья для отрисовки графика
	+ зарисовка площади под графиком
	[X] типы графиков - ломаный, сглаженный
	+ подпись осей
	> настройка начертания осей координат		
	настройка диапазона осей
	детализация основных тиков и побочных у осей