# pragma once

#include "singleton.h"
#include "types.hpp"

class Hud : public LazySingleton<Hud> {
public:
	void DrawSelf();
	const Vec2i& GetBagOffset();
	const int& GetSlotPixelSize();
private:
	Vec2i bagOffset{10, 10};
	int slotPixelSize{60};

	void DrawBag();
	void DrawPlayerStatusBar();
};

