#pragma once

typedef struct {
	float x;
	float y;
	float z;
} Point, Vector; // geometric 3D point

float vec_len(Vector);
float vec_dot(Vector, Vector);
Vector vec_plus(Vector, Vector);
Vector vec_minus(Vector, Vector);
Vector get_vec(Point, Point);
Point get_point(Point, Vector);
void normalize(Vector*);
Vector vec_scale(Vector, float);

