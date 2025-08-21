#include "menucraft.h"
#include "screen.hpp"
#include "texture.h"
#include "pickedslot.h"
#include "player.h"
#include "myassert.h"

MenuCraft::MenuCraft() {
	InitCrafts();
}

void MenuCraft::InitCrafts() {
	recipes = {
		CraftingRecipe {
			{
				texFlowerYellow, texUndefined, texFlowerYellow,
				texUndefined, texGrass, texUndefined,
				texFlowerYellow, texUndefined, texFlowerYellow,
			},
			texPotionEye,
		},
		CraftingRecipe {
			{
				texUndefined, texUndefined, texMushroom,
				texFlowerRed, texMushroom, texFlowerYellow,
				texMushroom, texUndefined, texUndefined,
			},
			texPotionLife,
		},
		CraftingRecipe {
			{
				texUndefined, texGrass, texUndefined,
				texFlowerRed, texFlowerRed, texFlowerRed,
				texUndefined, texGrass, texUndefined,
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

void MenuCraft::ProcessCraft() {
	if(pickedSlot.GetType() == CellType::CraftOutput && craftTable.outputItem != texUndefined
			&& player.objectInHand == texUndefined) {
		player.objectInHand = craftTable.outputItem;
		ClearCraftTable();
	}
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

	recipeReadinessIndicator.Init(
		{offset.x + menuSizes.x/4 + 4*static_cast<int>(slotSize*1.05),
		offset.y + menuSizes.y/3 + 0*slotSize},
		slotSize*2/3, CellType::Indicator
	);
}

float MenuCraft::GetRecipeReadinessRatio() {
	float maxRatio = 0.f;
	for(const auto& recipe : recipes) {
		float ingredientsNum = 0;
		float matchesNum = 0;
		for(int i = 0; i < 9; i++) {
			if(recipe.inputItems[i] == texUndefined)
				continue;

			ingredientsNum++;
			if(recipe.inputItems[i] == craftTable.inputItems[i])
				matchesNum++;
		}
		assert(ingredientsNum > 0);
		const float ratio = matchesNum / ingredientsNum;
		maxRatio = std::max(ratio, maxRatio);
	}
	return maxRatio;
}

void MenuCraft::CalcItemOutput() {
	craftTable.outputItem = texUndefined;
	for(const auto& recipe : recipes)
		if(craftTable.inputItems == recipe.inputItems) {
			craftTable.outputItem = recipe.outputItem;
			break;
		}
}

void MenuCraft::ClearCraftTable() {
	craftTable = {};
}

void MenuCraft::DrawSelf(const pixel_t slotSize) {
	if(isActive) {
		const Vec2i tmp_sizes = {static_cast<int>(screen.width/2), static_cast<int>(screen.height/2)};
		CalcOffset(tmp_sizes, slotSize);
		CalcItemOutput();

		DrawRectangle(offset, tmp_sizes);

		int tmp_count = 0;
		for(texture_t& itemTexture : craftTable.inputItems) {
			craftInputCells[tmp_count].ProcessWithTexture(&itemTexture);
			tmp_count += 1;
		}

		craftOutputCell.ProcessWithTexture(&craftTable.outputItem);

		recipeReadinessIndicator.DrawAsTexture(
			texSkillLightning,
			[&]() {glDisable(GL_ALPHA_TEST); glColor4f(1, 1, 1, GetRecipeReadinessRatio());},
			[&]() {glEnable(GL_ALPHA_TEST); glColor4f(1, 1, 1, 1);}
		);
	}
}

