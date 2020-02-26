#pragma once

class Figure {

protected:

	HWND hwnd;
	int x,y,size;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH hb;
	HPEN hp;

public:
	Figure(HWND hWnd, int size) : hwnd{ hWnd }, size{ size } {
		
	}

	COLORREF getRandomColor() {
		return RGB(rand() * 255, rand() * 255, rand() * 255);
	}

	void setRandomBrush() {
		hb = CreateSolidBrush(getRandomColor());
	}

	void setRandomPen() {
		hp = CreatePen(rand() * 7 - 1,1, getRandomColor());
	}

	virtual void draw() = 0;

	void setXY(int x, int y) {
		this->x = x;
		this->y = y;
	}


};

class Circle : public Figure {
public:
	Circle(HWND hWnd, int size) : Figure(hWnd, size) {};

	void draw() {
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, hb);
		Ellipse(hdc, x, y, x + size, y + size);
		SelectObject(hdc, hp);
		Ellipse(hdc, x, y, x + size, y + size);
		EndPaint(hwnd, &ps);
	}
};

class Triangle : public Figure {
public:
	Triangle(HWND hWnd, int size) : Figure(hWnd, size) {};

	void draw() {
		hdc = BeginPaint(hwnd, &ps);
		
		SelectObject(hdc, hb);

		POINT vertices[] = { {x, y}, {x + size, y + size}, {x - size, y + size} };
		Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
		SelectObject(hdc, hp);
		Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
		EndPaint(hwnd, &ps);
	}
};

class Rhomb : public Figure {
public:
	Rhomb(HWND hWnd, int size) : Figure(hWnd, size) {};

	void draw() {
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, hb);

		POINT vertices[] = { {x, y}, {x + size, y + size}, {x , y + 3*size}, {x -  size, y + size} };
		Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
		SelectObject(hdc, hp);
		Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
		EndPaint(hwnd, &ps);
	}
};

class Pentagon : public Figure {
public:
	Pentagon(HWND hWnd, int size) : Figure(hWnd, size) {};

	void draw() {
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, hb);

		POINT vertices[] = { {x, y}, {x + size, y + size}, 
		{x + size , y + 3 * size},  {x , y + 2*size}, {x - size, y + 2 * size}, };
		Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
		SelectObject(hdc, hp);
		Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
		EndPaint(hwnd, &ps);
	}
};