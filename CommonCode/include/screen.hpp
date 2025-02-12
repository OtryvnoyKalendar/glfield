#pragma once

#include "glcore.hpp"

class Screen {
private:
	void Init();
public:
	const char* name = "My OpenGL program";
	unsigned int width = 600;
	unsigned int height = 500;
	float aspectRatio = 1.f;
	sf::Window window;
	
	void CalcAspectRatio();
	void SetPerspective();
	void SetPerspectiveAndLighting();
	Screen();
	Screen(int _width, int _height, const char* _name);
	~Screen();
};

extern Screen screen;

