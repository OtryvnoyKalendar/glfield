#pragma once

#include <functional> // for std::function

#include "types.hpp"
#include "glcore.hpp"
#include "pixel.h"

void DrawRectangle(const Vec2i offset, const Vec2i pixelSizes);

enum class CellType {
	Inventory, Hand, CraftInput, CraftOutput, Effect,
};

class MenuCell {
public:
	void Init(const Vec2i offset, const pixel_t size, const CellType type);
	void SetOffset(const Vec2i offset);
	void SetSize(const pixel_t size);
	void SetType(const CellType type);

	CellType GetType();
	pixel_t GetSize();

	void ProcessWithTexture(const texture_t texture);
	void DrawAsTexture(const texture_t texture, std::function<void()> drawingEffectFunction);
private:
	CellType type{CellType::Inventory};
	Vec2i offset{};
	pixel_t size{30};
};

