#pragma once

#include <memory>

#include "glcore.hpp"
#include "singleton.h"

class Object {
public:
	float x, y, z;
	GLuint tex;
	float scale{1};

	void SetRandomPosition();
	bool IsPlayerNearby(float distance);
	bool IsPlayerFocusedOn();
};

class Objects : public LazySingleton<Objects> {
public:
	std::unique_ptr<Object[]> plants{nullptr};

	void DrawSelf();
	void Init();
private:
	int plantsNum{0};
};

