#include "screen.hpp"
#include "hud.h"
#include "player.h"
#include "texture.h"
#include "camera.h"
#include "myassert.h"

namespace {
	GLfloat verticesCrosshair[] = {
		0,1, 0,-1, -1,0, 1,0,
	};

	GLfloat verticesHeart[] = {
		0.5,0.25, 0.25,0, 0,0.25, 0.5,1, 1,0.25, 0.75,0,
	};
}

void DrawCrosshair(RgbaColor color, const float cursorSize,
		const float lineWidth) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verticesCrosshair);
	glPushMatrix();
		glColor4f(color.r, color.g, color.b, color.a);
		glTranslatef(screen.width*0.5f, screen.height*0.5f, 1);
		glScalef(cursorSize, cursorSize, 1);
		glLineWidth(lineWidth);
		glDrawArrays(GL_LINES, 0, 4);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Hud::DrawObjectInHand() {
	if(player.objectInHand != texUndefined && camera.GetCursorVisible()) {
		const pixel_t mx = sf::Mouse::getPosition(screen.window).x;
		const pixel_t my = sf::Mouse::getPosition(screen.window).y;
		const pixel_t offset = slotSize*3/4;
		objectInHandCell.SetOffset({mx-offset, my-offset});
		objectInHandCell.ProcessWithTexture(&player.objectInHand);
	}
}

void Hud::Init() {
	menuCraft.InitCrafts();
	InitMenuCells();
}

void Hud::InitMenuCells() {
	assert(player.GetBagCapacity() < cellsMaxNum);
	const pixel_t tmp_slotGap = 5;
	int tmp_count = 0;
	for(auto& cell : inventoryCells) {
		cell.Init({bagOffset.x + tmp_count*(slotSize+tmp_slotGap), bagOffset.y}, slotSize, CellType::Inventory);
		tmp_count += 1;
	}

	assert(player.GetEffectsNum() < cellsMaxNum);
	const pixel_t tmp_effectSize = 70;
	const pixel_t tmp_effectGap = 10;
	tmp_count = 0;
	for(auto& cell : effectCells) {
		cell.Init({effectsOffset.x + tmp_count*(tmp_effectSize+tmp_effectGap), effectsOffset.y}, tmp_effectSize, CellType::Effect);
		tmp_count += 1;
	}
	
	objectInHandCell.Init({0, 0}, slotSize, CellType::Hand);
}

void Hud::DrawBag() {
	int tmp_count = 0;
	for(texture_t& texture : player.bag) {
		inventoryCells[tmp_count].ProcessWithTexture(&texture);
		tmp_count += 1;
	}
}

void DrawHealth(const Vec2i offset, const int scale) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verticesHeart);
		const int tmp_healthMax = player.GetHealthStatus().healthMax;
		const int tmp_health = player.GetHealthStatus().health;
		const pixel_t tmp_gap = 2;
		for(int i = 0; i < tmp_healthMax; i++) {
			glPushMatrix();
				glTranslatef(offset.x + i*(scale+tmp_gap), offset.y, 0);
				glScalef(scale, scale, 1);
				if(i < tmp_health)
					glColor3f(1, 0, 0);
				else
					glColor3f(0, 0, 0);
				glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
			glPopMatrix();
		}
	glDisableClientState(GL_VERTEX_ARRAY);
}

const Vec2i& Hud::GetBagOffset() {
	return bagOffset;
}

const int& Hud::GetSlotSize() {
	return slotSize;
}

void DrawEffectIndicator(float ratio, pixel_t size) {
	if(ratio != 0.f) {
		glDisable(GL_ALPHA_TEST);
		glColor4f(1, 1, 1, 0.4);
		glScalef(size, size*ratio, 1);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glEnable(GL_ALPHA_TEST);
	}
}

void Hud::DrawEffects() {
	const std::vector<std::unique_ptr<Effect>>& tmp_effects = player.GetEffects();

	int tmp_count = 0;
	for(const auto& effect : tmp_effects) {
		const Counter tmp_time = effect->GetRemainingTime();

		float tmp_ratio = 0.f;
		if(tmp_time.GetEnable())
			tmp_ratio = static_cast<float>(tmp_time.GetValue()) / static_cast<float>(tmp_time.GetMax());

		const pixel_t tmp_size = effectCells[tmp_count].GetSize();
		effectCells[tmp_count].DrawAsTexture(
			effect->GetTexture(),
			[](){},
			[&]() {DrawEffectIndicator(tmp_ratio, tmp_size);}
		);

		tmp_count += 1;
	}
}

void Hud::DrawPlayerStatusBar() {
	DrawBag();
	DrawHealth(Vec2i({10, 80}), 30);
	DrawEffects();
	if(camera.GetCursorVisible())
		menuCraft.DrawSelf(slotSize);
	DrawObjectInHand();
}

void Hud::DrawSelf() {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, screen.width, screen.height, 0, -1, 1);

		if(!camera.GetCursorVisible())
			DrawCrosshair(RgbaColor({0.7, 0.7, 0.7, 0.45}), 15, 4);
		DrawPlayerStatusBar();

		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
}

