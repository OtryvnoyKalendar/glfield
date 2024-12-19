#include <cstring> // для memset
#include <iostream>
#include <cstdlib> // для exit

#include "glcore.hpp"
#include "texture.h"

GLuint texField;
GLuint texFlowerRed;
GLuint texFlowerYellow;
GLuint texGrass;
GLuint texMushroom;
GLuint texTree;
GLuint texTree2;

std::string texturesPath{};
void LoadResourcesPath() {
	char readBuf[1000];
	const char* openMessage = "resource directory(textures) = ";
	
	FILE* file = fopen("game.conf", "r");
	if(file == NULL) {
		printf("error reading game.conf\n");
		exit(1);
	}
	else {
		while(!feof(file))
			if(fscanf(file, "%s", readBuf) > 0) {
				printf("%s", openMessage);
				printf("%s\n", readBuf);
				texturesPath += readBuf;
			}
		fclose(file);
	}
}

void LoadTexture(const char* textureFileName, GLuint* _textureID) {
	sf::Image loadTexture;
	std::string currentPath = texturesPath + textureFileName;
	if(!loadTexture.loadFromFile(currentPath.c_str()))
		exit(1);

	glGenTextures(1, _textureID);
	glBindTexture(GL_TEXTURE_2D, *_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadTexture.getSize().x, loadTexture.getSize().y,
								0, GL_RGBA, GL_UNSIGNED_BYTE, loadTexture.getPixelsPtr());
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void InitTextures() {
	LoadResourcesPath();

	LoadTexture("field.png", &texField);
	LoadTexture("flower_red.png", &texFlowerRed);
	LoadTexture("flower_yellow.png", &texFlowerYellow);
	LoadTexture("grass.png", &texGrass);
	LoadTexture("mushroom.png", &texMushroom);
	LoadTexture("tree.png", &texTree);
	LoadTexture("tree2.png", &texTree2);
}

