#include <cstdlib>
#include <iostream>

#include "object.h"
#include "map.h"
#include "getrand.h"
#include "select.h"
#include "player.h"

namespace {
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
}

void Object::NormalizeHeight() {
	pos.z = map.GetHeight(pos.x, pos.y) - 0.1;
}

void Object::SetRandomPosition() {
	pos.x = GetRand(1, map.width-1);
	pos.y = GetRand(1, map.height-1);
	NormalizeHeight();
}

void Objects::DrawSelf() {
	// текстуры и другие настройки уже должны быть включены
	if(!IsSelectMode())
		glEnable(GL_TEXTURE_2D);
	glEnable(GL_VERTEX_ARRAY);
	glEnable(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verticesFlower);
	glTexCoordPointer(2, GL_FLOAT, 0, UVFlower);
	
	glNormal3f(0, 0, 1);

	SetSelectedToZero();
	int selectColor = 1;

	for(int i = 0; i < plantsNum; i++) {
		Object& p = plants[i];

		if(IsSelectMode() && player.IsNearbyToPos(10.5f, Vec3f({p.pos.x, p.pos.y, p.pos.z}))
			&& !(p.tex == texTree || p.tex == texTree2)) {
			glColor3ub(selectColor, 0, 0);
			AddToSelectedObjects({i, selectColor});
			selectColor += 1;
			if(selectColor >= 255)
				break;
		}
		else {
			float selfColorTmp{0.7};
			glColor3f(selfColorTmp, selfColorTmp, selfColorTmp);
		}

		glBindTexture(GL_TEXTURE_2D, p.tex);
		glPushMatrix();
			glTranslatef(p.pos.x, p.pos.y, p.pos.z);
			glScalef(p.scale, p.scale, p.scale);
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
	plants = std::make_unique<Object[]>(plantsNum);

	for(int i = 0; i < plantsNum; i++) {
		texture_t newTexture = texGrass;
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
		plants[i].SetRandomPosition();
	}
}

