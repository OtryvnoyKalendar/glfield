#include "player.h"
#include "texture.h"

Effect::Effect(const int uses, const int time, const int period, const texture_t texture) :
	remainingUses(uses), remainingTime(time), periodTime(period), drawTexture(texture) {}

bool Effect::IsEnd() {
	if(remainingTime())
		return true;

	if(periodTime() || !periodTime.GetEnable()) {
		Use();
		if(remainingUses())
			return true;
	}

	return false;
}

texture_t Effect::GetTexture() {
	return drawTexture;
}

Counter Effect::GetRemainingTime() {
	return remainingTime;
}

EffectHunger::EffectHunger()
	: Effect(disableCounterValue, disableCounterValue, 200, texSkillHunger) {};
EffectSpeedBoost::EffectSpeedBoost()
	: Effect(disableCounterValue, 1000, disableCounterValue, texSkillSpeed) {};
EffectNightVision::EffectNightVision()
	: Effect(disableCounterValue, 1000, disableCounterValue, texSkillEye) {};

void EffectHunger::Use() {
	player.ApplyHealthDelta(-1);
}

void EffectSpeedBoost::Use() {
	player.speed = 0.3f;
	player.SetJumpBoost(3.f);
}

void EffectNightVision::Use() {}

