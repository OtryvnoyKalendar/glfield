#pragma once

#include "glcore.hpp"

class Screen {
public:
	unsigned int width = 600;
	unsigned int height = 500;
	float aspectRatio = 1.f;
	sf::Window window;
	
	void CalcAspectRatio();
	void SetPerspective();
	void SetPerspectiveAndLighting();
	Screen();
	Screen(int _width, int _height, const char* _name, bool isFullscreen=false);
	~Screen() = default;
private:
	bool fullscreenInitialization{false};
	const char* name = "My OpenGL program";
	
	void Init();
};

extern Screen screen;

