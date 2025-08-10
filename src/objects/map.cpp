#define _USE_MATH_DEFINES // из за C++17
#include <cmath>

#include "map.h"
#include "getrand.h"
#include "camera.h"

void Map::CreateHill(int x, int y, int rad, int hillHeight) {
	for(int i = x-rad; i <= x+rad; i++)
		for(int j = y-rad; j <= y+rad; j++)
			if(IsCoordExist(i, j)) {
				float len = sqrt(pow(x-i, 2) + pow(y-j, 2));
				if(len < rad) {
					len = len / rad * M_PI_2;
					arrayCells[i][j].z += cos(len) * hillHeight;
				}
			}
}

float Map::GetHeight(float x, float y) {
	if(!IsCoordExist(x, y))
		return 0;

	int ix = static_cast<int>(x);
	int iy = static_cast<int>(y);

	float h1 = (1-(x - ix))*arrayCells[ix][iy].z + (x - ix)*arrayCells[ix+1][iy].z;
	float h2 = (1-(x - ix))*arrayCells[ix][iy+1].z + (x - ix)*arrayCells[ix+1][iy+1].z;

	return (1-(y-iy))*h1 + (y-iy)*h2;
}

void Map::Init(int _hillsNum) {
	hillsNum = _hillsNum;

	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++) {
			arrayCells[i][j].x = i;
			arrayCells[i][j].y = j;
			arrayCells[i][j].z = GetRand(0, 10) * 0.05f;
			arrayUV[i][j].u = i;
			arrayUV[i][j].v = j;
		}

	for(int i = 0; i < width-1; i++) {
		int pos = i * height;
		for(int j = 0; j < height-1; j++) {
			arrayIndexes[i][j][0] = pos;
			arrayIndexes[i][j][1] = pos + 1;
			arrayIndexes[i][j][2] = pos + 1 + height;

			arrayIndexes[i][j][3] = pos + 1 + height;
			arrayIndexes[i][j][4] = pos + height;
			arrayIndexes[i][j][5] = pos;

			pos++;
		}
	}

	for(int i = 0; i < hillsNum; i++)
		CreateHill(GetRand(0,width), GetRand(0,height), GetRand(0, 50), GetRand(0, 10));

	for(int i = 0; i < width-1; i++)
		for(int j = 0; j < height-1; j++)
			CalcNormals(arrayCells[i][j], arrayCells[i+1][j], arrayCells[i][j+1], &arrayNormals[i][j]);
}

Map::Map() {
	Init();
}

bool Map::IsCoordExist(float x, float y) {
	return x > 0 && x < width && y >= 0 && y < height;
}

void Map::DrawSelf() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_VERTEX_ARRAY);
	glEnable(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, arrayCells);
		glTexCoordPointer(2, GL_FLOAT, 0, arrayUV);
		glColor3f(0.7, 0.7, 0.7);
		glNormalPointer(GL_FLOAT, 0, arrayNormals);
		glBindTexture(GL_TEXTURE_2D, texField);
		glDrawElements(GL_TRIANGLES, indexesNum, GL_UNSIGNED_INT, arrayIndexes);
	glDisable(GL_NORMAL_ARRAY);
	glDisable(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

void Map::CalcNormals(Cell a, Cell b, Cell c, Cell* n) {
	float wrki;
	Cell v1, v2;

	v1.x = a.x - b.x;
	v1.y = a.y - b.y;
	v1.z = a.z - b.z;

	v2.x = b.x - c.x;
	v2.y = b.y - c.y;
	v2.z = b.z - c.z;

	n->x = v1.y * v2.z - v1.z * v2.y;
	n->y = v1.z * v2.x - v1.x * v2.z;
	n->z = v1.x * v2.y - v1.y * v2.x;

	wrki = std::sqrt(std::pow(n->x, 2) + std::pow(n->y, 2) + std::pow(n->z, 2));

	n->x /= wrki;
	n->y /= wrki;
	n->z /= wrki;
}

void Map::NormalizeHeight(const float xPos, const float yPos, float& zPos) {
	zPos = GetHeight(xPos, yPos) - 0.1;
}

void Map::LiftCameraOffGround(const float height) {
	NormalizeHeight(camera.x, camera.y, camera.z);
	camera.z += height;
}

Vec2f Map::GetRandomPosition() {
	return Vec2f{
		static_cast<float>(GetRand(1, width-1)),
		static_cast<float>(GetRand(1, height-1)),
	};
}

void Map::SetRandomPosition(float& xPos, float& yPos, float& zPos) {
	const Vec2f newPos = GetRandomPosition();
	xPos = newPos.x;
	yPos = newPos.y;
	NormalizeHeight(xPos, yPos, zPos);
}

