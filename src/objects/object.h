#pragma once

#include <memory>

#include "glcore.hpp"
#include "singleton.h"
#include "types.hpp"

class Object {
public:
	Vec3f pos;
	texture_t tex;
	float scale{1};
};

class Objects : public LazySingleton<Objects> {
public:
	std::unique_ptr<Object[]> plants{nullptr};

	void DrawSelf();
	void Init();
private:
	int plantsNum{0};
};

