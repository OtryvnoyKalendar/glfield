#pragma once

#include <vector>

#include "singleton.h"
#include "types.hpp"
#include "glcore.hpp"

struct HealthStatus {
	int health;
	int healthMax;
};

class Player : public LazySingleton<Player> {
public:
	const std::vector<texture_t>& GetBag();
	size_t GetBagCapacity();
	bool AddObjectToBag(texture_t object);
	HealthStatus GetHealthStatus();
	bool IsNearbyToPos(float distance, Vec3f pos);

	void Init(size_t bagCapacity, HealthStatus healthStatus);
	void Move();
	void ProcessInput();
private:
	HealthStatus healthStatus{15, 20};
	std::vector<texture_t> bag{};

	void InitBag(size_t bagCapacity);
	void SelectShape();
};

extern Player player; 

