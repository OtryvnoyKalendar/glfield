#define _USE_MATH_DEFINES // из за C++17
#include <cmath>

#include "program.hpp"
#include "screen.hpp"
#include "types.hpp"

#include "camera.h"
#include "map.h"
#include "texture.h"
#include "object.h"

Camera camera;
Screen screen(900, 700, "Amazing field");
Objects objects;
Map map;

bool Program::GetRunning() {
	return screen.window.isOpen();
}

void Program::Close() {
	running = false;
}

void Program::CheckMainEvents() {
	while(const std::optional event = screen.window.pollEvent()) {
		if(event->is<sf::Event::Closed>()) {
			screen.window.close();
		}
		else if(const auto* resized = event->getIf<sf::Event::Resized>()) {
			screen.width = resized->size.x;
			screen.height = resized->size.y;
			screen.SetPerspectiveAndLighting();
		}
		else if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if(keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				screen.window.close();
		}
	}
}

void Program::UpdateProgramLogic() {
	RenderGraphics();
	CheckMainEvents();
}

void PlayerMove() {
	if(!screen.window.hasFocus())
		return;

	const float jumpHeight{4.0};
	static float jump{0};
	const float jumpPlus{0.04};
	float dy{0};
	
	float playerHeight{1.7f};
	int moveForvard{0};
	int moveRight{0};

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
		moveForvard = 1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
		moveForvard = -1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
		moveRight = -1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
		moveRight = 1;

	if(jump > 0 && jump < 1) {
		jump += jumpPlus;
		if(jump > 1)
			jump = 0;
	}
	else {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space))
			jump += jumpPlus;
	}

	dy = std::sin(M_PI*jump)*jumpHeight;

	camera.MoveDirection(moveForvard, moveRight);
	camera.Apply();
	camera.z = map.GetHeight(camera.x, camera.y) + playerHeight + dy;
}


void DrawShapes() {
	glPushMatrix();
		PlayerMove();
		GLfloat position[] = {1, 0, 2, 0};
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		map.DrawSelf();
		objects.DrawSelf();
	glPopMatrix();
}

void Program::RenderGraphics() {
	glClearColor(0.6f, 0.8f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	DrawShapes();

	screen.window.display();
}

void Program::InitProgram() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.99);

	InitTextures();
	screen.SetPerspectiveAndLighting();
	camera.Init(0, 0, 1.7, 0, 0, 0.1, false);
	
	map.Init();
	objects.Init();
}

Program::Program() {
	InitProgram();
}

Program::~Program() {

}

