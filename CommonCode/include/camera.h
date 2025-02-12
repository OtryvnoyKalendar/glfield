#pragma once

class Camera {
public:
	float x, y, z;
	float speed{0};

	void Init(float _x, float _y, float _z, float _xRot, float _zRot, float _speed, bool _cursorVisible);
	void Apply();
	void ApplySettings();
	void Rotate(float xAngle, float zAngle);
	void AutoTurnByMouse(float mouseSensitivity);
	void MoveDirection(int moveForvard, int moveRight);
private:
	float xRot, zRot;
	bool cursorVisible;
};

extern Camera camera;

