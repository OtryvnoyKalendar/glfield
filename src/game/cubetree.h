#pragma once
#include "object.h"
#include "texture.h"

class Tree {
	int logsNum = 6;
	int leafsNum = 5*5*2 -2 + 3*3*2;
	int cubesNum = logsNum + leafsNum;
	GLuint tex = texWood;
public:
	Object* cubes = nullptr;
	void Init(float _x, float _y);
	void DrawSelf();
};

class Trees {
	Tree* trees = nullptr;
	int treesNum = 50;
public:
	~Trees();
	void Init(int _treesNum = 50);
	void DrawSelf();
};

