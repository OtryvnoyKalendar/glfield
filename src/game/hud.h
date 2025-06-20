# pragma once

#include "types.hpp"
#include "singleton.h"

class Hud : public LazySingleton<Hud> {
public:
	void DrawSelf();
private:
	void DrawCursor(RgbaColor color, const float cursorSize, const float lineWidth);
	void DrawPlayerStatusBar();
};

