#pragma once

#include "glcore.hpp"

extern float alpha;

class Sky {
public:
	void DrawSun();
	void ApplyLight();
	void DrawStars();
	void DrawBackground();
	
	void Init();
private:
	static const int starsNum{40};
	static const int verticesStarsNum = starsNum*3;
	GLfloat verticesStars[verticesStarsNum];
	float starsColorRatio[starsNum];
};

