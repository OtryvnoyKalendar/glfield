#pragma once

template <typename T>
struct Rect {
	T left;
	T top;
	T right;
	T bottom;
};

struct Vec2i {
	int x, y;
};

struct Vec2f {
	float x, y;
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

