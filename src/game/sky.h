#pragma once

#include "glcore.hpp"

extern float alpha;

class Sky {
public:
	static const int starsNum{40};
	static const int verticesStarsNum = starsNum*3;
	GLfloat verticesStars[verticesStarsNum];
	float starsColorRatio[starsNum];

	void DrawSun();
	void ApplyLight();
	void DrawStars();
	void DrawBackground();
	
	void Init();
};

