#pragma once

#include <array>

#include "types.hpp"
#include "glcore.hpp"
#include "pixel.h"
#include "drawmenu.h"

class CraftingRecipe {
public:
	CraftingRecipe(std::array<texture_t, 9> _inputItems, texture_t _outputItem);
	CraftingRecipe();

	std::array<texture_t, 9> inputItems{};
	texture_t outputItem{};
};

class MenuCraft {
public:
	bool isActive{true};

	MenuCraft();

	void DrawSelf(const pixel_t slotSize);
	const Vec2i& GetOffset();
private:
	Vec2i offset;
	pixel_t gap{5};
	CraftingRecipe craftTable;
	std::vector<CraftingRecipe> recipes;
	std::array<MenuCell, 9> craftInputCells{};
	MenuCell craftOutputCell{};

	void CalcItemOutput();
	void CalcOffset(const Vec2i menuSizes, const pixel_t slotSize);
};

