#include <cstdlib>
#include <iostream>
#include <cmath>

#include "object.h"
#include "map.h"
#include "getrand.h"
#include "camera.h"

GLfloat verticesFlower[] = {
	-0.5,0,0, 0.5,0,0, 0.5,0,1, -0.5,0,1,
	0,-0.5,0, 0,0.5,0, 0,0.5,1, 0,-0.5,1,
};

GLfloat UVFlower[] = {
	0,1, 1,1, 1,0, 0,0, 0,1, 1,1, 1,0, 0,0,
};

GLuint indexesFlower[] = {
	0,1,2, 2,3,0, 4,5,6, 6,7,4,
};

bool Object::IsPlayerFocusedOn() {
	return true;
}

bool Object::IsPlayerNearby(float distance) {
	return std::sqrt(std::pow(x - camera.x, 2) + std::pow(y - camera.y, 2) + std::pow(z - camera.z, 2)) <= distance;
}

void Objects::DrawSelf() {
	// текстуры и другие настройки уже должны быть включены
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_VERTEX_ARRAY);
	glEnable(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verticesFlower);
	glTexCoordPointer(2, GL_FLOAT, 0, UVFlower);
	
	glNormal3f(0, 0, 1);

	for(int i = 0; i < plantsNum; i++) {
		float selfColorTmp{0.7};
		if(plants[i].IsPlayerNearby(5.f) && plants[i].IsPlayerFocusedOn())
			selfColorTmp = 0.3;
		glColor3f(selfColorTmp, selfColorTmp, selfColorTmp);

		glBindTexture(GL_TEXTURE_2D, plants[i].tex);
		glPushMatrix();
			glTranslatef(plants[i].x, plants[i].y, plants[i].z);
			glScalef(plants[i].scale, plants[i].scale, plants[i].scale);
			glDrawElements(GL_TRIANGLES, std::size(indexesFlower), GL_UNSIGNED_INT, indexesFlower);
		glPopMatrix();
	}
	
	glDisable(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

void Objects::Init() {
	int grassNum = 2000;
	int mushroomNum = 30;
	int treeNum = 0;

	plantsNum = grassNum + mushroomNum + treeNum;
	plants = new Object[plantsNum];
	if(plants == nullptr) {
		printf("memory allocation error\n");
		exit(1);
	}

	for(int i = 0; i < plantsNum; i++) {
		GLuint newTexture = texGrass;
		float newScale = 1;

		if(i < grassNum) {
			newScale = 0.5 + GetRand(0, 4)*0.1;
			if(GetRand(1, 10) > 9)
				newTexture = texFlowerYellow;
			else if(GetRand(1, 10) > 9)
				newTexture = texFlowerRed;
			else {
				newTexture = texGrass;
				newScale = 0.8 + GetRand(0, 5)*0.1;
			}
		}
		else if(i < grassNum + mushroomNum) {
			newTexture = texMushroom;
			newScale = 0.3 + GetRand(0, 3)*0.1;
		}
		else {
			if(GetRand(1, 10) > 4)
				newTexture = texTree;
			else
				newTexture = texTree2;
			newScale = 4 + GetRand(0, 14);
		}

		plants[i].tex = newTexture;
		plants[i].scale = newScale;
		plants[i].x = GetRand(1, map.width-1);
		plants[i].y = GetRand(1, map.height-1);
		plants[i].z = map.GetHeight(plants[i].x, plants[i].y) - 0.1;
	}
}

void Objects::FreeMemory() {
	if(plants != nullptr) {
		delete [] plants;
		plants = nullptr;
	}
}

Objects::~Objects() {
	FreeMemory();
}

