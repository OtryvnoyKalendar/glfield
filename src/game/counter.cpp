#include <cstdlib>
#include <iostream>

#include "counter.h"

Counter::Counter(const int max) {
	enable = max != disableCounterValue;
	maxValue = max;
	if(!enable)
		return;
	if(max < 0) {
		printf("Counter constructor error: a negative argument\n");
		exit(1);
	}
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

