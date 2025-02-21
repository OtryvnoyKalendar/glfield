#pragma once

struct SelectObject {
	int plantIndexInArray;
	int colorIndex;
};

bool IsSelectMode();
void SetSelectedToZero();
void AddToSelectedObjects(SelectObject object);

