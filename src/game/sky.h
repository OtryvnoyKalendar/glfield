#pragma once

#include "glcore.hpp"
#include "singleton.h"

extern float alpha;

class Sky : public LazySingleton<Sky> {
public:
	void DrawSun();
	void ApplyLight();
	void DrawStars();
	void DrawBackground();
	
	void Init();
private:
	static const int starsNum{40};
	static const int verticesStarsNum = starsNum*3;
	static GLfloat verticesStars[verticesStarsNum];
};

