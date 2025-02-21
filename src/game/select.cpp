#include <array>

#include "program.h"
#include "screen.hpp"
#include "select.h"
#include "object.h"
#include "animation.h"

extern Objects objects;

const int selectMaxNum{255};
static bool isSelectMode{false};
static int selectedObjectsNum{};
static std::array<Selectobj, selectMaxNum> selectArray{};

void AddToSelectedObjects(Selectobj object) {
	selectArray[selectedObjectsNum] = object;
	selectedObjectsNum += 1;
}

void SetSelectedToZero() {
	selectedObjectsNum = 0;
}

bool IsSelectMode() {
	return isSelectMode;
}

void Program::SelectShape() {
	isSelectMode = true;
	RenderGraphics();
	isSelectMode = false;

	GLubyte color[3];

	float mx = sf::Mouse::getPosition(screen.window).x;
	float my = sf::Mouse::getPosition(screen.window).y;
	
	glReadPixels(mx, my, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
	if(color[0] > 0) {
		for(int i = 0; i < selectedObjectsNum; i++)
			if(selectArray[i].colorIndex == color[0]) {
				animPickingUp.SetObject(&objects.plants[selectArray[i].plantIndexInArray]);
				// objects.plants[selectArray[i].plantIndexInArray].z = -1000;
			}
	}
}

