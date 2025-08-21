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
Hud hud;

void InitPlayer() {
	const size_t bagCapacity = 10;
	player.Init(bagCapacity, HealthStatus({15, 20}));
	map.SetRandomPosition(camera.x, camera.y, camera.z);
	hud.menuCraft.ClearCraftTable();
	Sky().RandomizeSunAngle();
}

void CheckPlayerDeath() {
	if(player.GetHealthStatus().health == 0)
		InitPlayer();
}

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
	CheckPlayerDeath();
}

void DrawShapes() {
	Sky().ChangeSunAngle();

	glPushMatrix();
		if(!IsSelectMode()) {
			Sky().DrawStars();
			Sky().DrawSun();
		}
		player.ProcessEffects();
		player.Move(!camera.GetCursorVisible());
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
		hud.DrawSelf();
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

void Program::InitScene() {
	audio.PlayMusic(mscRelax);

	screen.SetPerspectiveAndLighting();

	const float xRot = 100; const float zRot = 270;
	camera.Init(Vec3f({10, 10, 1.7}), Vec2f({xRot, zRot}), 0.1, false);

	map.Init(10);
	objects.Init();
	cubetrees.Init(60);
	Sky::GetInstance().Init();

	InitPlayer();
	hud.Init();
}

void Program::InitProgram() {
	InitRenderingState();

	InitTextures();
	InitSounds();

	InitScene();
}

Program::Program() {
	InitProgram();
}

