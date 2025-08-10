# pragma once

#include "singleton.h"

class Hud : public LazySingleton<Hud> {
public:
	void DrawSelf();
private:
	void DrawPlayerStatusBar();
};

