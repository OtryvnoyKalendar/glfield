#include <iostream>

#include "screen.hpp"

void Screen::Init() {
	const sf::ContextSettings settings {
		.depthBits = 24,
		.stencilBits = 8,
		.antiAliasingLevel = 4,
		.majorVersion = 4,
		.minorVersion = 6,
	};

	const auto nameTmp = static_cast<sf::String>(name);
	const sf::Vector2u sizesTmp = {width, height};
	sf::State stateTmp = sf::State::Windowed;
	if(fullscreenInitialization)
		stateTmp = sf::State::Fullscreen;
	window.create(sf::VideoMode(sizesTmp), nameTmp, stateTmp, settings);
	
	window.setVerticalSyncEnabled(true);
	if(!window.setActive(true))
		std::cerr << "The window didn't focus" << std::endl;
}

void Screen::CalcAspectRatio() {
	aspectRatio = (float)width / (float)height;
}

void Screen::SetPerspective() {
	glViewport(0, 0, screen.width, screen.height);
	glLoadIdentity();
	CalcAspectRatio();
	glScalef(1.f/aspectRatio, 1.f/aspectRatio, 1);
	float sz{0.1};
	glFrustum(-aspectRatio*sz, aspectRatio*sz, -sz, sz, sz*2, 100);
}

void Screen::SetPerspectiveAndLighting() {
	glMatrixMode(GL_PROJECTION);
	SetPerspective();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

Screen::Screen() {
	Init();
}

Screen::Screen(int _width, int _height, const char* _name, bool isFullscreen) : width(_width), height(_height),  fullscreenInitialization(isFullscreen) {
	name = _name;
	Init();
}

Screen::~Screen() {

}

