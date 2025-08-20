#include "menucraft.h"
#include "screen.hpp"
#include "texture.h"

MenuCraft::MenuCraft() {
	recipes = {
		CraftingRecipe {
			{
				texUndefined, texUndefined, texUndefined,
				texUndefined, texFlowerYellow, texUndefined,
				texUndefined, texUndefined, texUndefined,
			},
			texPotionEye,
		},
		CraftingRecipe {
			{
				texUndefined, texUndefined, texUndefined,
				texUndefined, texFlowerRed, texUndefined,
				texUndefined, texUndefined, texUndefined,
			},
			texPotionLife,
		},
		CraftingRecipe {
			{
				texUndefined, texUndefined, texUndefined,
				texUndefined, texGrass, texUndefined,
				texUndefined, texUndefined, texUndefined,
			},
			texPotionSpeed,
		},
	};
}

CraftingRecipe::CraftingRecipe(std::array<texture_t, 9> _inputItems, texture_t _outputItem)
	: inputItems(_inputItems), outputItem(_outputItem) {}

CraftingRecipe::CraftingRecipe() : outputItem(texUndefined) {
	inputItems.fill(texUndefined);
}

void MenuCraft::CalcOffset(const Vec2i menuSizes, const pixel_t slotSize) {
	offset = {
		static_cast<int>(screen.width/4),
		static_cast<int>(screen.height/4),
	};

	int tmp_count = 0;
	for(auto& cell : craftInputCells) {
		const int dx = tmp_count % 3;
		const int dy = tmp_count / 3;
		cell.Init(
			{offset.x + menuSizes.x/4 + dx*(slotSize+gap), offset.y + menuSizes.y/3 + dy*(slotSize+gap)},
			slotSize, CellType::CraftInput
		);

		tmp_count += 1;
	}

	craftOutputCell.Init(
		{offset.x + menuSizes.x/4 + 4*slotSize, offset.y + menuSizes.y/3 + 1*slotSize},
		slotSize, CellType::CraftOutput
	);
}

void MenuCraft::CalcItemOutput() {
	craftTable.outputItem = texUndefined;
	for(const auto& recipe : recipes)
		if(craftTable.inputItems == recipe.inputItems) {
			craftTable.outputItem = recipe.outputItem;
			break;
		}
}

void MenuCraft::DrawSelf(const pixel_t slotSize) {
	if(isActive) {
		const Vec2i tmp_sizes = {static_cast<int>(screen.width/2), static_cast<int>(screen.height/2)};
		CalcOffset(tmp_sizes, slotSize);
		CalcItemOutput();

		DrawRectangle(offset, tmp_sizes);

		int tmp_count = 0;
		for(const auto& itemTexture : craftTable.inputItems) {
			craftInputCells[tmp_count].ProcessWithTexture(itemTexture);
			tmp_count += 1;
		}

		craftOutputCell.ProcessWithTexture(craftTable.outputItem);
	}
}

const Vec2i& MenuCraft::GetOffset() {
	return offset;
}

