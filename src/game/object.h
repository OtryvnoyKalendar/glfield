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
public:
	Object* plants = nullptr;

	void DrawSelf();
	void Init();
	void FreeMemory();
	~Objects();
private:
	int plantsNum = 0;
};

