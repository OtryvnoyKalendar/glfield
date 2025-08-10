#pragma once

#include "glcore.hpp"
#include "singleton.h"

class Sky : public LazySingleton<Sky> {
public:
	void DrawSun();
	void ApplyLight();
	void ChangeSunAngle();
	void RandomizeSunAngle();
	void DrawStars();
	void DrawBackground();
	
	void Init();
private:
	static const int starsNum{40};
	static const int verticesStarsNum = starsNum*3;
	static GLfloat verticesStars[verticesStarsNum];
};

