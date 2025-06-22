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
#include "sounds.h"
#include "select.h"
#include "animation.h"
#include "hud.h"
#include "player.h"
#include "onepress.h"

Screen screen(900, 700, "Amazing field");
Camera camera;
AudioManager audio;

static Trees cubetrees;
Objects objects;
Map map;
Player player;

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

void Program::UpdateLogic() {
	animPickingUp.Play();
	RenderGraphics();
	CheckMainEvents();
	if(!camera.GetCursorVisible() && IsMouseClicked::Left()) {
		audio.PlaySound(sndLaserShoot);
		SelectShape();
	}
	player.ProcessInput();
}

void ChangeSunAngle() {
	alpha += 0.02f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::U))
		alpha += 1.2f;
	if(alpha > 180)
		alpha -= 360;
}

void DrawShapes() {
	ChangeSunAngle();

	glPushMatrix();
		if(!IsSelectMode()) {
			Sky().DrawStars();
			Sky().DrawSun();
		}
		player.Move();
		Sky().ApplyLight();

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
		Sky().DrawBackground();
		glEnable(GL_LIGHTING);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	DrawShapes();
	if(!IsSelectMode()) {
		Hud().DrawSelf();
		screen.window.display();
	}
}

void InitRenderingState() {
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
}

void Program::InitProgram() {
	InitRenderingState();

	InitTextures();
	InitSounds();
	audio.PlayMusic(mscRelax);

	screen.SetPerspectiveAndLighting();
	camera.Init(10, 10, 1.7, 100, 270, 0.1, false);

	map.Init(10);
	objects.Init();
	cubetrees.Init(60);
	Sky::GetInstance().Init();
	Hud::GetInstance();

	player.Init(10, HealthStatus({15, 20}));
}

Program::Program() {
	InitProgram();
}

