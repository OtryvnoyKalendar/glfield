#include <cstdlib>
#include <ctime>

int GetRand(int min, int max) {
	static bool initialized = false;
	if(!initialized) {
		srand(time(nullptr));
		initialized = true;
	}

	return min + rand() % (max - min + 1);
}

