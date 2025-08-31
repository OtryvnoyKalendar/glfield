#pragma once

#include "types.hpp"

class Camera {
public:
	float x, y, z;
	float speed{0};

	void Apply();
	void ApplySettings();

	void Init(Vec3f position, Vec2f rotation, float speed, bool cursorVisible);
	void AutoTurnByMouse(const float mouseSensitivity);
	Vec2f GetMovementOffset(const int moveForvard, const int moveRight);
	void MoveDirection(const int moveForvard, const int moveRight, float speed);
	void SetCursorVisible(bool visible);

	bool GetCursorVisible();
	float GetXRot();
	float GetZRot();
	float GetXRotRad();
	float GetZRotRad();
private:
	float xRot, zRot; // Grad
	bool cursorVisible;

	void Rotate(float xAngle, float zAngle);
};

extern Camera camera;

