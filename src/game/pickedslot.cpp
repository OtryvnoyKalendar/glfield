#include "pickedslot.h"
#include "screen.hpp"

PickedSlot pickedSlot{};

void PickedSlot::Clear() {
	m_type = CellType::Undefined;
	m_texture = nullptr;
}

void PickedSlot::Set(const Vec2i cellOffset, const pixel_t cellSize, const CellType type, texture_t* texture) {
	if(texture && (type == CellType::Inventory || type == CellType::CraftInput || type == CellType::CraftOutput)) {
		const int mx = sf::Mouse::getPosition(screen.window).x;
		const int my = sf::Mouse::getPosition(screen.window).y;

		if((mx >= cellOffset.x && mx <= cellOffset.x+cellSize) &&
				(my >= cellOffset.y && my <= cellOffset.y+cellSize)) {
			m_texture = texture;
			m_type = type;
			return;
		}
	}
}

CellType PickedSlot::GetType() {
	return m_type;
}

texture_t* PickedSlot::GetTexture() {
	return m_texture;
}

