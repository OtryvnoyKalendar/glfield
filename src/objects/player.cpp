#include <cmath>
#include <algorithm> // for std::clamp, std::count

#include "screen.hpp"
#include "camera.h"
#include "player.h"
#include "map.h"
#include "sounds.h"
#include "onepress.h"
#include "hud.h"
#include "texture.h"

bool Player::IsNearbyToPos(const float distance, const Vec3f pos) {
	using namespace std;

	return sqrt(
		pow(pos.x - camera.x, 2) +
		pow(pos.y - camera.y, 2) +
		pow(pos.z - camera.z, 2)
	) <= distance;
}

size_t Player::GetObjectsNum(const texture_t objectType) {
	return std::count(bag.begin(), bag.end(), objectType);
}

const std::vector<std::unique_ptr<Effect>>& Player::GetEffects() {
	return effects;
}

void Player::RemoveObjects(const texture_t objectType, const size_t number) {
	size_t removed = 0;
	for (auto& i : bag) {
		if (i == objectType) {
			i = texUndefined;
			if(++removed == number)
				break;
		}
	}
}

void Player::ProcessBagUsage() {
	const int dx = Hud().GetBagOffset().x;
	const int dy = Hud().GetBagOffset().y;
	const int slotSize = Hud().GetSlotPixelSize();

	const float mx = sf::Mouse::getPosition(screen.window).x;
	const float my = sf::Mouse::getPosition(screen.window).y;

	if(IsMouseClicked::Left() && (my > dy && my < dy+slotSize))
		for(size_t i = 0; i < GetBagCapacity(); i++)
			if((mx > dx + i*slotSize) && (mx < dx + (i+1)*slotSize)) {
				const size_t necessaryForEffect = 4;
				if(bag[i] == texMushroom) {
					ApplyHealthDelta(2);
				}
				else if(bag[i] == texFlowerRed) {
					if(GetObjectsNum(texFlowerRed) >= necessaryForEffect) {
						RemoveObjects(texFlowerRed, necessaryForEffect);
						effects.emplace_back(std::make_unique<EffectSpeedBoost>());
						continue;
					}
				}
				else if(bag[i] == texFlowerYellow) {
					if(GetObjectsNum(texFlowerYellow) >= necessaryForEffect) {
						RemoveObjects(texFlowerYellow, necessaryForEffect);
						effects.emplace_back(std::make_unique<EffectNightVision>());
						continue;
					}
				}
				bag[i] = texUndefined;
			}
}

void Player::SetJumpBoost(float boost) {
	if(boost < 0)
		boost = 0;
	jumpBoost = boost;
}

void Player::ProcessInput() {
	if(!screen.window.hasFocus())
		return;

	if(IsKeyPressedOnce(sf::Keyboard::Scan::E))
		camera.SetCursorVisible(!camera.GetCursorVisible());

	if(IsKeyPressedOnce(sf::Keyboard::Scan::K))
		ApplyHealthDelta(-healthStatus.healthMax);

	if(camera.GetCursorVisible())
		ProcessBagUsage();
}

void Player::SetHeight(bool jumpAllowed) {
	static float jump{0};
	const float jumpPlus{0.04};
	float dy{0};

	if(jump > 0 && jump < 1) {
		jump += jumpPlus;
		if(jump > 1)
			jump = 0;
	}
	else {
		if(jumpAllowed && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
			jump += jumpPlus;
			audio.PlaySound(sndGrass);
		}
	}
	dy = std::sin(M_PI*jump)*jumpHeight*jumpBoost;
	map.LiftCameraOffGround(selfHeight + dy);
	jumpBoost = 1.f;
}

void Player::Move(const bool moveAllowed) {
	if(!screen.window.hasFocus())
		return;
	
	int moveForvard{0};
	int moveRight{0};

	if(moveAllowed) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
			moveForvard = 1;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
			moveForvard = -1;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
			moveRight = -1;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
			moveRight = 1;
	}

	if(moveAllowed)
		camera.MoveDirection(moveForvard, moveRight, speed);
	SetHeight(moveAllowed);
	camera.Apply();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift))
		speed = runSpeed;
	else
		speed = normalSpeed;
}

void Player::OnDeath() {}

void Player::ProcessEffects() {
	for(auto it = effects.begin(); it != effects.end(); ) {
		if((*it)->IsEnd())
			it = effects.erase(it);
		else
			++it;
	}
}

void Player::ApplyHealthDelta(const int delta) {
	healthStatus.health += delta;

	if(healthStatus.health <= 0)
		OnDeath();

	healthStatus.health = std::clamp(healthStatus.health, 0, healthStatus.healthMax);
}

const std::vector<texture_t>& Player::GetBag() {
	return bag;
}

size_t Player::GetBagCapacity() {
	return bag.size();
}

HealthStatus Player::GetHealthStatus() {
	return healthStatus;
}

void Player::InitBag(size_t bagCapacity) {
	bag.assign(bagCapacity, texUndefined);
}

bool Player::HasEffect(const std::type_info& effectType) {
	for(const auto& i : effects)
		if(typeid((*i)) == effectType)
			return true;
	return false;
}

void Player::Init(size_t bagCapacity, HealthStatus healthStatus) {
	this->healthStatus = healthStatus;

	InitBag(bagCapacity);
	if(!HasEffect(typeid(EffectHunger)))
		effects.emplace_back(std::make_unique<EffectHunger>());
}

bool Player::AddObjectToBag(texture_t object) {
	for(texture_t& i : bag)
		if(i == texUndefined) {
			i = object;
			return true;
		}

	return false;
}

