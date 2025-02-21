#pragma once

#include "glcore.hpp"

class Object {
public:
	float x, y, z;
	GLuint tex;
	float scale = 1;

	bool IsPlayerNearby(float distance);
	bool IsPlayerFocusedOn();
};

class Objects {
private:
	Object* plants = nullptr;
	int plantsNum = 0;
public:
	void DrawSelf();

	void Init();
	void FreeMemory();
	~Objects();
};

