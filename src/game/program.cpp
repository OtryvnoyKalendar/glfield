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
	return running;
}

void Program::Close() {
	running = false;
}

void Program::CheckMainEvents() {
	sf::Event event;

	while(screen.window.pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			Close();
		}
		else if(event.type == sf::Event::Resized) {
			screen.width = event.size.width;
			screen.height = event.size.height;
			screen.SetPerspectiveAndLighting();
		}
		else if(event.type == sf::Event::KeyPressed) {
			if (event.key.scancode == sf::Keyboard::Scan::Escape)
				Close();
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

	const float jumpHeight{5.0};
	const float gravity{0.1};
	static float velocityY{0};
	
	float playerHeight{1.7f};
	int moveForvard{0};
	int moveRight{0};

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		moveForvard = 1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		moveForvard = -1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		moveRight = -1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		moveRight = 1;

	if(velocityY <= 0) {
		velocityY = 0;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			velocityY += jumpHeight;
	}
	else {
		velocityY -= gravity;
	}

	camera.MoveDirection(moveForvard, moveRight);
	camera.Apply();
	camera.z = map.GetHeight(camera.x, camera.y) + playerHeight + velocityY;
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

