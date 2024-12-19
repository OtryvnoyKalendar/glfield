#include "program.hpp"

int main() {
	Program program;

	while(program.GetRunning()) {
		program.UpdateProgramLogic();
	}

	return 0;
}

