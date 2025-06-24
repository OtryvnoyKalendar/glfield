#define _USE_MATH_DEFINES // C++17
#include <cmath>

#include "camera.h"
#include "glcore.hpp"
#include "types.hpp"
#include "screen.hpp"

void Camera::Init(float _x, float _y, float _z, float _xRot, float _zRot, float _speed, bool _cursorVisible) {
	x = _x; y = _y; z = _z;
	xRot = _xRot; zRot = _zRot;
	speed = _speed;
	cursorVisible = _cursorVisible;

	ApplySettings();
}

void Camera::Rotate(float xAngle, float zAngle) {
	zRot += zAngle;
	if(zRot < 0)
		zRot += 360;
	if(zRot > 360)
		zRot -= 360;

	xRot += xAngle;
	if(xRot < 0)
		xRot = 0;
	if(xRot > 180)
		xRot = 180;
}

void Camera::Apply() {
	glRotatef(-xRot, 1, 0, 0);
	glRotatef(-zRot, 0, 0, 1);
	glTranslatef(-x, -y, -z);
}

void Camera::AutoTurnByMouse(float mouseSensitivity) {
	Vec2i cursor{};
	cursor.x = sf::Mouse::getPosition(screen.window).x;
	cursor.y = sf::Mouse::getPosition(screen.window).y;
	const Vec2i base = screen.GetCenter();
	Rotate((base.y-cursor.y) / mouseSensitivity, (base.x-cursor.x) / mouseSensitivity);
	sf::Mouse::setPosition(sf::Vector2i(base.x, base.y), screen.window);
}

void Camera::ApplySettings() {
	screen.window.setMouseCursorVisible(cursorVisible);
}

bool Camera::GetCursorVisible() {
	return cursorVisible;
}

void Camera::SetCursorVisible(bool visible) {
	cursorVisible = visible;
	if(visible == false) {
		const Vec2i center = screen.GetCenter();
		sf::Mouse::setPosition(sf::Vector2i(center.x, center.y), screen.window);
	}
	ApplySettings();
}

float Camera::GetXRot() {
	return xRot;
}

float Camera::GetZRot() {
	return zRot;
}

float Camera::GetXRotRad() {
	return xRot * (M_PI / 180.f);
}

float Camera::GetZRotRad() {
	return zRot * (M_PI / 180.f);
}

void Camera::MoveDirection(int moveForvard, int moveRight) {
	float angle = -zRot / 180.f * M_PI;
	float currentSpeed{speed};
	
	if(moveForvard > 0) {
		angle += moveRight > 0 ? M_PI_4 : (moveRight < 0 ? -M_PI_4 : 0);
	}
	else if(moveForvard < 0) {
		angle += M_PI + (moveRight > 0 ? -M_PI_4 : (moveRight < 0 ? M_PI_4 : 0));
	}
	else {
		angle += moveRight > 0 ? M_PI_2 : -M_PI_2;
		if(moveRight == 0)
			currentSpeed = 0;
	}
	
	if(currentSpeed != 0) {
		x += sin(angle) * currentSpeed;
		y += cos(angle) * currentSpeed;
	}

	AutoTurnByMouse(6.0);
}

void Camera::MoveDirection(int moveForvard, int moveRight, float _speed) {
	const float speedSave{speed};
	speed = _speed;
	MoveDirection(moveForvard, moveRight);
	speed = speedSave;
}

