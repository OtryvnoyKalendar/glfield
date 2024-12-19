#pragma once

#include "glcore.hpp"

enum ObjectType {
	objFlowerRed, objFlowerYellow, objGrass, objTree,
};

class Object {
public:
	float x, y, z;
	//ObjectType type; // не используется пока
	GLuint tex;
	float scale = 1;
};

class Objects {
private:
	Object* plants = nullptr;
	int plantsNum = 0;
public:
	void DrawSelf();

	void Init();
	void FreeMemory();
	Objects();
	~Objects();
};

