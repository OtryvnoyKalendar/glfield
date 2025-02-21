#pragma once

struct Selectobj {
	int plantIndexInArray;
	int colorIndex;
};

bool IsSelectMode();
void SetSelectedToZero();
void AddToSelectedObjects(Selectobj object);

