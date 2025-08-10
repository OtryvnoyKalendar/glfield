#include "player.h"

Effect::Effect(const int uses, const int time, const int period) :
	remainingUses(uses), remainingTime(time), periodTime(period) {}

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


EffectHunger::EffectHunger()
	: Effect(disableCounterValue, disableCounterValue, 200) {};
EffectSpeedBoost::EffectSpeedBoost()
	: Effect(disableCounterValue, 1000, disableCounterValue) {};
EffectNightVision::EffectNightVision()
	: Effect(disableCounterValue, 1000, disableCounterValue) {};

void EffectHunger::Use() {
	player.ApplyHealthDelta(-1);
}

void EffectSpeedBoost::Use() {
	player.speed = 0.6f;
}

void EffectNightVision::Use() {}

