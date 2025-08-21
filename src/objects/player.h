#pragma once

#include <vector>

#include "singleton.h"
#include "types.hpp"
#include "glcore.hpp"
#include "effect.h"
#include "texture.h"

struct HealthStatus {
	int health;
	int healthMax;
};

class Player : public LazySingleton<Player> {
public:
	float speed{0.f};
	float normalSpeed{0.08f};
	float runSpeed{0.15f};
	texture_t objectInHand{texUndefined};
	std::vector<texture_t> bag{};

	size_t GetBagCapacity();
	bool AddObjectToBag(texture_t object);

	const std::vector<std::unique_ptr<Effect>>& GetEffects();
	bool HasEffect(const std::type_info& effectType);
	size_t GetEffectsNum();
	HealthStatus GetHealthStatus();
	bool IsNearbyToPos(const float distance, const Vec3f pos);
	void ApplyHealthDelta(const int delta);
	void SetJumpBoost(float boost);

	size_t GetObjectsNum(const texture_t objectType);
	void RemoveObjects(const texture_t objectType, const size_t number);
	Vec2i GetCursorInventoryPosition();

	void ClearInventory();
	void ClearEffects();
	void ClearAll();

	void Init(size_t bagCapacity, HealthStatus healthStatus);
	void Move(const bool moveAllowed);
	void ProcessInput();
	void ProcessEffects();
private:
	float selfHeight{1.7f};
	float jumpHeight{4.f};
	float jumpBoost{1.f};
	Vec2i cursorInventoryPosition{};

	HealthStatus healthStatus{15, 20};
	std::vector<std::unique_ptr<Effect>> effects{};

	void OnDeath();
	void InitBag(size_t bagCapacity);
	void SetHeight(bool jumpAllowed);
	void ProcessBagUsage();
	void UpdateCursorInventoryPosition();
};

extern Player player; 

