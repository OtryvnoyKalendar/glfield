#pragma once

#include <array>

#include "singleton.h"
#include "menucraft.h"
#include "drawmenu.h"
#include "pixel.h"

class Hud : public LazySingleton<Hud> {
public:
	MenuCraft menuCraft{};

	void Init();
	void DrawSelf();
	const Vec2i& GetBagOffset();
	const int& GetSlotSize();
private:
	Vec2i bagOffset{10, 10};
	Vec2i effectsOffset{10, 125};
	pixel_t slotSize{60};

	static const int cellsMaxNum{100};
	std::array<MenuCell, cellsMaxNum> inventoryCells{};
	std::array<MenuCell, cellsMaxNum> effectCells{};
	MenuCell objectInHandCell{};

	void InitMenuCells();
	void DrawObjectInHand();
	void DrawBag();
	void DrawEffects();
	void DrawPlayerStatusBar();
};

extern Hud hud;

