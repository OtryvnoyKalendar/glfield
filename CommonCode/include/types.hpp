#pragma once

#ifndef __WIN32__
typedef struct {
	int x, y;
} COORD, POINT;

struct POINTFLOAT {
	float x, y;
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


// this is not present in windows.h
struct RECTFLOAT {
	float left;
	float top;
	float right;
	float bottom;
};

struct Vec3f {
	float x, y, z;
};

struct RgbColor {
	float r, g, b;
};

struct RgbaColor {
	float r, g, b, a;
};

