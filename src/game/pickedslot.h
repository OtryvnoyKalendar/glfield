#pragma once

#include "drawmenu.h"
#include "texture.h"

class PickedSlot {
public:
	void Set(const Vec2i cellOffset, const pixel_t cellSize, const CellType type, texture_t* texture);
	CellType GetType();
	texture_t* GetTexture();
	void Clear();
private:
	CellType m_type{CellType::Undefined};
	texture_t* m_texture{};
};

extern PickedSlot pickedSlot;

