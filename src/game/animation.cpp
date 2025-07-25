#include <cstdlib> 

#include "animation.h"
#include "camera.h"
#include "player.h"

ObjectAnimation animPickingUp;

void ObjectAnimation::SetObject(Object* _object) {
	if(_object == nullptr)
		exit(1);
	object = _object;
	stepsNum = 10;
	dx = (camera.x - object->pos.x) / stepsNum;
	dy = (camera.y - object->pos.y) / stepsNum;
	dz = (camera.z - object->pos.z - object->scale -0.2) / stepsNum;
}

void ObjectAnimation::Play() {
	if(object != nullptr) {
		object->pos.x += dx;
		object->pos.y += dy;
		object->pos.z += dz;
		stepsNum -= 1;
		if(stepsNum < 1) {
			if(player.AddObjectToBag(object->tex))
				object->SetRandomPosition();
			else
				object->NormalizeHeight();

			object = nullptr;
		}
	}
}

