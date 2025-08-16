#include <iostream>
#undef NDEBUG
#include <cassert>

#include "counter.h"

Counter::Counter(const int max) {
	enable = max != disableCounterValue;
	maxValue = max;
	if(!enable)
		return;
	assert(max >= 0 && "Counter constructor error: a negative argument");
}

bool Counter::operator()() {
	if(!enable)
		return false;

	curValue++;
	if(curValue >= maxValue) {
		curValue = 0;
		return true;
	}
	return false;
}

bool Counter::GetEnable() const {
	return enable;
}

int Counter::GetValue() const {
	return curValue;
}

int Counter::GetMax() const {
	return maxValue;
}

