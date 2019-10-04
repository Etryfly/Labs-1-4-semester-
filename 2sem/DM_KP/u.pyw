import itertools
from tkinter import *
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

Visited = []
GPath = []  # гамильтонов путь
GPathBuff = []
Atmp = []

EPath = []

list_ABC = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
list_num = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10']


def preCreateGraph():  # функция для создания матрицы связности
    rt1 = Toplevel(root)
    rt1.title("Таблица связности")
    global n, list_grid

    n = sca.get()  # получаем размер графа

    def CreateGraph():  # функция для записи значений в глобальную переменную матрицы связности
        global A, Visited
        Visited = [False] * n
        A = np.zeros((n, n))
        for i in range(n):
            for j in range(n):
                A[i, j] = list_grid[i][j].get()
        rt1.destroy()

    list_grid = [[IntVar() for i in range(n)] for j in range(n)]  # сюда считывается активность ячеек

    for i in range(n):
        for j in range(n):
            Checkbutton(rt1, variable=list_grid[i][j], onvalue=1, offvalue=0).grid(row=i + 1, column=j + 1)
            if i == 0:
                Label(rt1, text=list_num[j]).grid(row=i, column=j + 1)
            if j == 0:
                Label(rt1, text=list_num[i]).grid(row=i + 1, column=j)
    Button(rt1, text="СОЗДАТЬ", command=CreateGraph).grid(columnspan=n + 1)
    rt1.mainloop()


# данная функция выполнится при нажатии кнопки АЛГОРИТМ
def algo():
    c = 0
    global GPath, Visited, GPathBuff, EPath, Atmp

    tex.delete(1.0, END)
    del EPath[:]
    EPath = []
    bufRes = 0

    del GPathBuff[:]
    GPathBuff = []

    for i in range(n):
        Visited = [False] * n
        del GPath[:]

        res = hamilton(i)
        if res == 1:
            tex.insert(1.0, "\nГамильтонов цикл:" + '-'.join(str(x+1) for x in GPath))
            bufRes = 1
            break
        elif res == 2:
            GPathBuff = GPath.copy()
            bufRes = res

    if bufRes == 2:
        tex.insert(1.0, "\nГамильтонов путь:" + '-'.join(str(x+1) for x in GPathBuff))
    if bufRes == 0:
        tex.insert(1.0, ''.join(str(x) for x in "\nГамильтонова пути нет"))

    # проверка на существование Эйлерпова цикла

    n_count = 0

    for i in range(n):
        count = 0
        for j in range(n):
            if A[i][j] == 1:
                count += 1
        if count % 2 != 0:
            n_count += 1
    #n_count = 0 -> цикл
    #n_count = 2 -> путь
    Atmp = A.copy()
    euler(0)

    if n_count == 0:
        #EPath.pop(0)
        tex.insert(1.0, "Эйлеров цикл:" + '-'.join(str(x+1) for x in EPath))
    elif n_count == 2:
        tex.insert(1.0, "Эйлеров путь:" + '-'.join(str(x+1) for x in EPath))
    else:
        tex.insert(1.0, "Эйлерова пути(цикла) нет")

    #Сделать tmp массива A для


def hamilton(curr):
    # 1 - цикл
    # 2 - путь
    # 0 - в графе нет гамильтонова пути
    curr = int(curr)
    GPath.append(curr)

    Visited[curr] = True

    for next in range(n):
        if A[curr][next] == 1 and not Visited[next]:
            state = hamilton(next)

            return state

    if len(GPath) == n and not Visited.count(False):
        if A[GPath[-1]][GPath[0]] == 1:
            return 1
        else:
            return 2

    Visited[curr] = False
    GPath.pop()

    return 0


def euler(curr):
    for i in range(n):
        if Atmp[curr][i] == 1:
            Atmp[curr][i] = 0
            Atmp[i][curr] = 0
            euler(i)
    EPath.append(curr)

def picture():
    G = nx.DiGraph(A)
    labelsdict = {}  # словарь с метками
    for i in range(n):
        labelsdict[i] = list_num[i]
    pos = nx.circular_layout(G)  # расчитываю координаты узлов
    nx.draw(G, pos)  # рисую в соответствии с рассчитанными кординатами
    nx.draw_networkx_labels(G, pos, labels=labelsdict)  # подрисовываю метки
    plt.show()


############################функции GUI

############################основная часть программы
root = Tk()
root.title("Гамильтоновы и Эйлеровы пути(циклы)")
label1 = Label(root, text="Пути(циклы)")
label2 = Label(root, text="Число узлов графа")
tex = Text(width=40, heigh=3, wrap=WORD)
sca = Scale(root, orient=HORIZONTAL, length=120, from_=3, to=10, tickinterval=1, resolution=1)
but1 = Button(root, text="СОЗДАТЬ ГРАФ", command=preCreateGraph)
but2 = Button(root, text="АЛГОРИТМ", command=algo)
but3 = Button(root, text="ИЗОБРАЖЕНИЕ ГРАФА", command=picture)
label2.pack()
sca.pack()
but1.pack()
but3.pack()
but2.pack()
label1.pack()
tex.pack()
root.mainloop()
