#include <cstdlib>
#include <ctime>

int GetRand(int min, int max) {
	static bool initialized = false;
	if(!initialized) {
		srand(time(NULL));
		initialized = true;
	}

	return min + rand() % (max - min + 1);
}

