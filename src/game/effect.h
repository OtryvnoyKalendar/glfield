#pragma once

#include "counter.h"
#include "glcore.hpp"

class Effect {
public:
    Effect(const int uses, const int time, const int period, const texture_t texture);
	Effect() = delete;
	bool IsEnd();
	texture_t GetTexture();
protected:
	virtual void Use() = 0;
private:
	Counter remainingUses;
	Counter remainingTime;
	Counter periodTime;
	texture_t drawTexture;
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

