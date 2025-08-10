#include "glcore.hpp"
#include "texture.h"
#include "resource.h"
#include "gameconf.h"

texture_t texUndefined = -1;

texture_t texField;
texture_t texFlowerRed;
texture_t texFlowerYellow;
texture_t texGrass;
texture_t texMushroom;
texture_t texTree;
texture_t texTree2;
texture_t texWood;

void InitTextures() {
	LoadConfigInfo();
	namespace rt = res::texture;
	// rt::set_normal_load(GL_REPEAT, GL_LINEAR); // прикольный эффект
	rt::set_normal_load(GL_REPEAT, GL_NEAREST);

	rt::normal_load("field.png", &texField);
	rt::normal_load("flower_red.png", &texFlowerRed);
	rt::normal_load("flower_yellow.png", &texFlowerYellow);
	rt::normal_load("grass.png", &texGrass);
	rt::normal_load("mushroom.png", &texMushroom);
	rt::normal_load("tree.png", &texTree);
	rt::normal_load("tree2.png", &texTree2);
	rt::normal_load("wood.png", &texWood);
}

