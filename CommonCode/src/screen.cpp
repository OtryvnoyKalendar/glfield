#include "screen.hpp"

void Screen::Init() {
	sf::ContextSettings settings;
	settings.depthBits = 24;              // Биты глубины
	settings.stencilBits = 8;             // Биты трафарета
	settings.antialiasingLevel = 4;       // Уровень сглаживания
	settings.majorVersion = 4;            // Основная версия OpenGL
	settings.minorVersion = 6;            // Минорная версия OpenGL
	
	window.create(sf::VideoMode(width, height), name, sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	window.setActive(true);
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

Screen::Screen(int _width, int _height, const char* _name) : width(_width), height(_height) {
	name = _name;
	Init();
}

Screen::~Screen() {

}

