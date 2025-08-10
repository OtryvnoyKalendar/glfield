#pragma once

#include "types.hpp"

class Camera {
public:
	float x, y, z;
	float speed{0};

	void Apply();
	void ApplySettings();

	void Init(Vec3f position, Vec2f rotation, float speed, bool cursorVisible);
	void Rotate(float xAngle, float zAngle);
	void AutoTurnByMouse(float mouseSensitivity);
	void MoveDirection(int moveForvard, int moveRight);
	void MoveDirection(int moveForvard, int moveRight, float _speed);
	void SetCursorVisible(bool visible);

	bool GetCursorVisible();
	float GetXRot();
	float GetZRot();
	float GetXRotRad();
	float GetZRotRad();
private:
	float xRot, zRot; // Grad
	bool cursorVisible;
};

extern Camera camera;

