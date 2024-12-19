#pragma once

#include "cell.h"
#include "types.hpp"
#include "glcore.hpp"
#include "texture.h"

class Map {
public:
	static const int width = 100;
	static const int height = 100;

	void Init();
	void DrawSelf();
	bool IsCoordExist(float x, float y);
	float GetHeight(float x, float y);
	Map();
private:
	static const int indexesNum = (width-1)*(height-1)*6;

	Cell arrayNormals[width][height];
	Cell arrayCells[width][height];
	UV arrayUV[width][height];
	GLuint arrayIndexes[width-1][height-1][6];

	void CalcNormals(Cell a, Cell b, Cell c, Cell *n);
	void CreateHill(int x, int y, int rad, int hillHeight);
};

extern Map map;
