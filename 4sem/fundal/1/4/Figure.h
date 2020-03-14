#pragma once

#include <vector>
#include <Windows.h>

class Figure {

private:

	HWND hwnd;
	PAINTSTRUCT ps;
	
	HBRUSH hb;
	HPEN hp;
	

public:
	std::vector<POINT> points;

	Figure(HWND hWnd) : hwnd{ hWnd } {
		setRandomBrush();
	}

	COLORREF getRandomColor() {
		return RGB(rand() * 255, rand() * 255, rand() * 255);
	}

	void setRandomBrush() {
		hb = CreateSolidBrush(getRandomColor());
	}

	

	void addPoint(POINT p) {
		points.push_back(p);
	}

	void draw(HDC hdc) {
		

		

		SelectObject(hdc, hb);


		Polygon(hdc, points.data(), points.size());
		
		
	}

	void move(int x, int y) {
		for (int i = 0; i < points.size(); ++i) {
			points[i].x += x;
			points[i].y += y;
		}
	}




};


