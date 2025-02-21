#pragma once

#include "object.h"

class ObjectAnimation {
public:
	void SetObject(Object* _object);
	void Play();
private:
	float dx, dy, dz;
	int stepsNum;
	Object* object{nullptr};
};

extern ObjectAnimation animPickingUp;

