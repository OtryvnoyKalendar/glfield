#pragma once

#include "cell.h"
#include "types.hpp"
#include "glcore.hpp"
#include "texture.h"
#include "singleton.h"

class Map : public LazySingleton<Map> {
public:
	static const int width = 100;
	static const int height = 100;

	void Init(int _hillsNum=12);
	void DrawSelf();
	bool IsCoordExist(const float x, const float y);
	float GetHeight(const float x, const float y);
	float GetHeight(const float x, const float y, const bool isPlayerCheck);
	Map();

	void NormalizeHeight(const float xPos, const float yPos, float& zPos);
	void NormalizeHeight(const float xPos, const float yPos, float& zPos, const bool isPlayerCheck);
	void LiftCameraOffGround(const float height);
	void SetRandomPosition(float& xPos, float& yPos, float& zPos);
	Vec2f GetRandomPosition();
private:
	int hillsNum;
	static const int indexesNum = (width-1)*(height-1)*6;

	Cell arrayNormals[width][height];
	Cell arrayCells[width][height];
	UV arrayUV[width][height];
	GLuint arrayIndexes[width-1][height-1][6];

	void CalcNormals(Cell a, Cell b, Cell c, Cell* n);
	void CreateHill(int x, int y, int rad, int hillHeight);
};

extern Map map;

