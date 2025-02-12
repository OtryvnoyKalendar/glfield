#pragma once

// нет в window.h
struct RECTFLOAT {
	float left;
	float top;
	float right;
	float bottom;
};

#ifndef __WIN32__
struct COORD {
	int x;
	int y;
};

struct POINT {
	int x;
	int y;
};

struct POINTFLOAT {
	float x;
	float y;
};

struct RECT {
	long left;
	long top;
	long right;
	long bottom;
};
#else
#include <windows.h>
#endif

struct Color {
	float r, g, b;
};

