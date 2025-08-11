#pragma once

#include "counter.h"

class Effect {
public:
    Effect(const int uses, const int time, const int period);
	Effect() = delete;
	bool IsEnd();
protected:
	virtual void Use() = 0;
private:
	Counter remainingUses;
	Counter remainingTime;
	Counter periodTime;
};

#define EFFECT_CLASS(className)             \
class className : public Effect {           \
public:                                     \
	className();                           	\
	void Use() override;                    \
};

EFFECT_CLASS(EffectHunger)
EFFECT_CLASS(EffectSpeedBoost)
EFFECT_CLASS(EffectNightVision)

