#include "glcore.hpp"
#include "screen.hpp"
#include "hud.h"

namespace {
	GLfloat verticesCursor[] = {
		0,1, 0,-1, -1,0, 1,0,
	};

	GLuint indexesCursor[] = {0, 1, 2, 3};
}

void Hud::DrawCursor(RgbaColor color, const float cursorSize,
		const float lineWidth) {
	glColor4f(color.r, color.g, color.b, color.a);
	glLineWidth(lineWidth);
	glScalef(cursorSize/screen.aspectRatio, cursorSize, 1);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verticesCursor);
	glDrawElements(GL_LINES, std::size(indexesCursor), GL_UNSIGNED_INT,
					indexesCursor);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Hud::DrawPlayerStatusBar() {}

void Hud::DrawSelf() {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		DrawCursor(RgbaColor({0.7, 0.7, 0.7, 0.45}), 0.03, 4);
		DrawPlayerStatusBar();

		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
}

