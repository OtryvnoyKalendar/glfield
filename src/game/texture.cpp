#include <cstring> // для memset
#include <iostream>
#include <cstdlib> // для exit
#include <string> // для оператора += для std::string

#include "glcore.hpp"
#include "texture.h"
#include "resource.h"
#include "gameconf.h"

GLuint texField;
GLuint texFlowerRed;
GLuint texFlowerYellow;
GLuint texGrass;
GLuint texMushroom;
GLuint texTree;
GLuint texTree2;
GLuint texWood;

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

