#pragma once

#include <memory>

#include "object.h"
#include "texture.h"
#include "singleton.h"

class Tree {
public:
	std::unique_ptr<Object[]> cubes{nullptr};

	void Init(float _x, float _y);
	void DrawSelf();
private:
	int logsNum = 6;
	int leafsNum = 5*5*2 -2 + 3*3*2;
	int cubesNum = logsNum + leafsNum;
	GLuint tex = texWood;
};

class Trees : public LazySingleton<Trees> {
public:
	void Init(int _treesNum = 50);
	void DrawSelf();
private:
	std::unique_ptr<Tree[]> trees{nullptr};
	int treesNum = 50;
};

