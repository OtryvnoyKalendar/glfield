#include "cubetree.h"
#include "map.h"
#include "getrand.h"

namespace {
	GLfloat verticesCube[] = {
		0,0,0, 1,0,0, 1,1,0, 0,1,0,
		0,0,1, 1,0,1, 1,1,1, 0,1,1,
		// повторяется для других текстурных координат
		0,0,0, 1,0,0, 1,1,0, 0,1,0,
		0,0,1, 1,0,1, 1,1,1, 0,1,1,
	};

	GLfloat UVTreeLog[] = {
		0.5,0.5, 1,0.5, 1,0, 0.5,0,
		0.5,0.5, 1,0.5, 1,0, 0.5,0,
		0,0.5, 0.5,0.5, 0,0.5, 0.5,0.5,
		0,0, 0.5,0, 0,0, 0.5,0,
	};

	GLfloat UVTreeLeaf[] = {
		0,1, 0.5,1, 0.5,0.5, 0,0.5,
		0,1, 0.5,1, 0.5,0.5, 0,0.5,
		0,0.5, 0.5,0.5, 0,0.5, 0.5,0.5,
		0,1, 0.5,1, 0,1, 0.5,1,
	};

	GLuint indexesCube[] = {
		0,1,2, 2,3,0, 4,5,6, 6,7,4, 8,9,13, 13,12,8,
		9,10,14, 14,13,9, 10,11,15, 15,14,10, 11,8,12, 12,15,11,
	};
}

void Tree::DrawSelf() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_VERTEX_ARRAY);
	glEnable(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verticesCube);
	glColor3f(0.7, 0.7, 0.7);
	glNormal3f(0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	
	for(int i = 0; i < cubesNum; i++) {
		if(i < logsNum)
			glTexCoordPointer(2, GL_FLOAT, 0, UVTreeLog);
		else
			glTexCoordPointer(2, GL_FLOAT, 0, UVTreeLeaf);

		glPushMatrix();
			Vec3f& p = cubes[i].pos;
			glTranslatef(p.x, p.y, p.z);
			glDrawElements(GL_TRIANGLES, std::size(indexesCube), GL_UNSIGNED_INT, indexesCube);
		glPopMatrix();
	}
	
	glDisable(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

void Tree::Init(float x, float y) {
	float z = map.GetHeight(x+0.5, y+0.5) - 0.5;
	cubes = std::make_unique<Object[]>(cubesNum);

	for(int i = 0; i < logsNum; i++) {
		cubes[i].pos.x = x;
		cubes[i].pos.y = y;
		cubes[i].pos.z = z+i;
	}

	int pos = logsNum;
	for(int k = 0; k < 2; k++)
		for(int i = x-2; i <= x+2; i++)
			for(int j = y-2; j <= y+2; j++)
				if(i != x || j != y) {
					cubes[pos].pos.x = i;
					cubes[pos].pos.y = j;
					cubes[pos].pos.z = z + logsNum -2 + k;
					pos++;
				}
	
	for(int k = 0; k < 2; k++)
		for(int i = x-1; i <= x+1; i++)
			for(int j = y-1; j <= y+1; j++) {
				cubes[pos].pos.x = i;
				cubes[pos].pos.y = j;
				cubes[pos].pos.z = z + logsNum + k;
				pos++;
			}
}

void Trees::Init(int treesNum) {
	this->treesNum = treesNum;
	trees = std::make_unique<Tree[]>(treesNum);
	for(int i = 0; i < treesNum; i++)
		trees[i].Init(GetRand(2, map.width-2), GetRand(2, map.height-2));
}

void Trees::DrawSelf() {
	for(int i = 0; i < treesNum; i++)
		trees[i].DrawSelf();
}

