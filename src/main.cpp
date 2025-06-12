#include "program.h"

int main() {
	Program program;

	while(program.IsRunning())
		program.UpdateLogic();
}

