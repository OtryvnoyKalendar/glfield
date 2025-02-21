#include <cstdlib> 

#include "animation.h"
#include "camera.h"

ObjectAnimation animPickingUp;

void ObjectAnimation::SetObject(Object* _object) {
	if(_object == nullptr)
		exit(1);
	object = _object;
	stepsNum = 10;
	dx = (camera.x - object->x) / stepsNum;
	dy = (camera.y - object->y) / stepsNum;
	dz = (camera.z - object->z - object->scale -0.2) / stepsNum;
}

void ObjectAnimation::Play() {
	if(object != nullptr) {
		object->x += dx;
		object->y += dy;
		object->z += dz;
		stepsNum -= 1;
		if(stepsNum < 1) {
			object->SetRandomPosition();
			object = nullptr;
		}
	}
}

