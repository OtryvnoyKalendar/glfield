#include "glcore.hpp"
#include "screen.hpp"
#include "types.hpp"
#include "hud.h"
#include "player.h"
#include "texture.h"
#include "camera.h"

namespace {
	GLfloat verticesCrosshair[] = {
		0,1, 0,-1, -1,0, 1,0,
	};

	GLfloat verticesBagSlot[] = {
		0,0, 1,0, 1,1, 0,1,
	};
	GLfloat UVBagSlot[] = {
		0,0, 1,0, 1,1, 0,1,
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

void Hud::DrawBag() {
	const size_t tmp_capacity = player.GetBagCapacity();
	const std::vector<texture_t>& tmp_bag = player.GetBag();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verticesBagSlot);
	glTexCoordPointer(2, GL_FLOAT, 0, UVBagSlot);
		for(size_t i = 0; i < tmp_capacity; i++) {
			glPushMatrix();
				glTranslatef(bagOffset.x + i*slotPixelSize, bagOffset.y, 0);
				glScalef(slotPixelSize, slotPixelSize, 1);
				glColor3ub(110, 95, 73);
				glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

				if(tmp_bag[i] != texUndefined) {
					glColor3f(1, 1, 1);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, tmp_bag[i]);
					glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
					glDisable(GL_TEXTURE_2D);
				}

				glColor3ub(160, 146, 116);
				glLineWidth(3);
				glDrawArrays(GL_LINE_LOOP, 0, 4);
			glPopMatrix();
		}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void DrawHealth(const Vec2i offset, const int scale) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verticesHeart);
		int tmp_healthMax = player.GetHealthStatus().healthMax;
		int tmp_health = player.GetHealthStatus().health;
		for(int i = 0; i < tmp_healthMax; i++) {
			glPushMatrix();
				glTranslatef(offset.x + i*scale, offset.y, 0);
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

const int& Hud::GetSlotPixelSize() {
	return slotPixelSize;
}

void DrawEffects(const Vec2i offset, const int pixelSize, int gap) {
	const std::vector<std::unique_ptr<Effect>>& tmp_effects = player.GetEffects();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glVertexPointer(2, GL_FLOAT, 0, verticesBagSlot);
	glTexCoordPointer(2, GL_FLOAT, 0, UVBagSlot);
		int tmp_count = 0;
		for(const auto& effect : tmp_effects) {
			glPushMatrix();
				glTranslatef(offset.x, offset.y + tmp_count*(pixelSize+gap), 0);
				glScalef(pixelSize, pixelSize, 1);
				glColor3f(1, 1, 1);
				glBindTexture(GL_TEXTURE_2D, effect->GetTexture());
				glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glPopMatrix();

			tmp_count += 1;
		}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

void Hud::DrawPlayerStatusBar() {
	DrawBag();
	DrawHealth(Vec2i({10, 80}), 30);
	DrawEffects(Vec2i({10, 125}), 70, 10);
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

