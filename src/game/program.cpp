#define _USE_MATH_DEFINES // C++17
#include <cmath>

#include "program.h"
#include "screen.hpp"
#include "types.hpp"
#include "camera.h"
#include "map.h"
#include "object.h"
#include "cubetree.h"
#include "sky.h"
#include "cursor.h"
#include "sounds.h"
#include "select.h"

Camera camera;
Screen screen(900, 700, "Amazing field");
Objects objects;
Map map;
Trees cubetrees;
Sky sky;
AudioManager audio;

bool Program::IsRunning() {
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

bool IsMouseCliced() {
	static bool mousePressed = false;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if(!mousePressed) {
			mousePressed = true;
			return true;
		}
	}
	else
		mousePressed = false;

	return false;
}

void Program::UpdateLogic() {
	RenderGraphics();
	CheckMainEvents();
	if(IsMouseCliced()) {
		audio.PlaySound(sndLaserShoot);
		SelectShape();
	}
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
			jump += jumpPlus;
			audio.PlaySound(sndGrass);
		}
	}

	dy = std::sin(M_PI*jump)*jumpHeight;

	float runSpeed{0};
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift))
		runSpeed = 0.25f;
	else
		runSpeed = 0.1f;

	camera.MoveDirection(moveForvard, moveRight, runSpeed);
	camera.Apply();
	camera.z = map.GetHeight(camera.x, camera.y) + playerHeight + dy;
}

void DrawShapes() {
	alpha += 0.02f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::U))
		alpha += 1.2f;
	if(alpha > 180)
		alpha -= 360;

	glPushMatrix();
		if(!IsSelectMode()) {
			sky.DrawStars();
			sky.DrawSun(); // нужно перед camera.Apply();
		}
		PlayerMove();
		sky.ApplyLight();

		map.DrawSelf();
		objects.DrawSelf();
		cubetrees.DrawSelf();
	glPopMatrix();
}

void Program::RenderGraphics() {
	if(IsSelectMode()) {
		glClearColor(0, 0, 0, 0);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
	}
	else {
		sky.DrawBackground();
		glEnable(GL_LIGHTING);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	DrawShapes();
	if(!IsSelectMode()) {
		DrawCursor(0.7, 0.7, 0.7, 0.45, 0.03, 4);
		screen.window.display();
	}
}

void Program::InitProgram() {
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.4);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	InitTextures();
	InitSounds();
	audio.PlayMusic(mscRelax);

	screen.SetPerspectiveAndLighting();
	camera.Init(10, 10, 1.7, 100, 270, 0.1, false);

	map.Init(10);
	objects.Init();
	cubetrees.Init(60);
	sky.Init();
}

Program::Program() {
	InitProgram();
}

Program::~Program() {

}

