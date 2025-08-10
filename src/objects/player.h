#pragma once

#include <vector>

#include "singleton.h"
#include "types.hpp"
#include "glcore.hpp"
#include "effect.h"

struct HealthStatus {
	int health;
	int healthMax;
};

class Player : public LazySingleton<Player> {
public:
	float speed{0.f};
	float normalSpeed{0.1f};
	float runSpeed{0.25f};

	const std::vector<texture_t>& GetBag();
	size_t GetBagCapacity();
	bool AddObjectToBag(texture_t object);
	HealthStatus GetHealthStatus();
	bool IsNearbyToPos(const float distance, const Vec3f pos);
	void ApplyHealthDelta(const int delta);
	bool HasEffect(const std::type_info& effectType);

	void Init(size_t bagCapacity, HealthStatus healthStatus);
	void Move(const bool moveAllowed);
	void ProcessInput();
	void ProcessEffects();
private:
	float selfHeight{1.7f};
	float jumpHeight{4.f};
	HealthStatus healthStatus{15, 20};
	std::vector<texture_t> bag{};
	std::vector<std::unique_ptr<Effect>> effects{};

	void OnDeath();
	void InitBag(size_t bagCapacity);
	void SetHeight(bool jumpAllowed);
	void ProcessBagUsage();
};

extern Player player; 

