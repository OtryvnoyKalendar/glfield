#pragma once

#ifndef WIN32
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

#endif
#endif

struct Color {
	float r, g, b;
};

