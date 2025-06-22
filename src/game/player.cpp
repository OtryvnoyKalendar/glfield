#include <cmath>

#include "screen.hpp"
#include "camera.h"
#include "player.h"
#include "map.h"
#include "sounds.h"
#include "onepress.h"

bool Player::IsNearbyToPos(float distance, Vec3f pos) {
	using namespace std;

	return sqrt(
		pow(pos.x - camera.x, 2) +
		pow(pos.y - camera.y, 2) +
		pow(pos.z - camera.z, 2)
	) <= distance;
}

void Player::ProcessInput() {
	if(!screen.window.hasFocus())
		return;

	if(IsKeyPressedOnce(sf::Keyboard::Scan::E))
		camera.SetCursorVisible(!camera.GetCursorVisible());
}

void Player::Move() {
	if(!screen.window.hasFocus())
		return;

	const bool moveAllowed = !camera.GetCursorVisible();
	const float jumpHeight{4.0};
	static float jump{0};
	const float jumpPlus{0.04};
	float dy{0};
	
	float playerHeight{1.7f};
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

	if(jump > 0 && jump < 1) {
		jump += jumpPlus;
		if(jump > 1)
			jump = 0;
	}
	else {
		if(moveAllowed && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
			jump += jumpPlus;
			audio.PlaySound(sndGrass);
		}
	}

	dy = std::sin(M_PI*jump)*jumpHeight;

	float runSpeed{0};
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift))
		runSpeed = 0.25f;
	else
		runSpeed = 0.1f;

	if(moveAllowed)
		camera.MoveDirection(moveForvard, moveRight, runSpeed);
	camera.z = map.GetHeight(camera.x, camera.y) + playerHeight + dy;
	camera.Apply();
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

void Player::Init(size_t bagCapacity, HealthStatus healthStatus) {
	InitBag(bagCapacity);
	this->healthStatus = healthStatus;
}

bool Player::AddObjectToBag(texture_t object) {
	for(texture_t& i : bag)
		if(i == texUndefined) {
			i = object;
			return true;
		}

	return false;
}

