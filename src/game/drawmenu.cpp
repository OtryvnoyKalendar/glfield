#include "drawmenu.h"
#include "texture.h"
#include "myassert.h"

namespace {
	GLfloat verticesCell[] = {
		0,0, 1,0, 1,1, 0,1,
	};
	GLfloat UvCell[] = {
		0,0, 1,0, 1,1, 0,1,
	};
}

void DrawFrame() {
	static const pixel_t FrameLineWidth{3};
	glColor3ub(160, 146, 116);
	glLineWidth(FrameLineWidth);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void DrawRectangle(const Vec2i offset, const Vec2i pixelSizes) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verticesCell);
		glPushMatrix();
			glTranslatef(offset.x, offset.y, 0);
			glScalef(pixelSizes.x, pixelSizes.y, 1);
			glColor3ub(110, 95, 73);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	
			DrawFrame();
		glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawCellTexture(const texture_t texture) {
	if(texture != texUndefined) {
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glDisable(GL_TEXTURE_2D);
	}
}

void EnableCellGlState() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verticesCell);
	glTexCoordPointer(2, GL_FLOAT, 0, UvCell);
}

void DisableCellGlState() {
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void MenuCell::Init(const Vec2i offset, const pixel_t size, const CellType type) {
	SetOffset(offset);
	SetSize(size);
	SetType(type);
}

void MenuCell::SetOffset(const Vec2i offset) {
	this->offset = offset;
}

void MenuCell::SetSize(const pixel_t size) {
	assert(size >= 0);
	this->size = size;
}

void MenuCell::SetType(const CellType type) {
	this->type = type;
}

pixel_t MenuCell::GetSize() {
	return size;
}

CellType MenuCell::GetType() {
	return type;
}

void MenuCell::ProcessWithTexture(const texture_t texture) {
	EnableCellGlState();
		glPushMatrix();
			glTranslatef(offset.x, offset.y, 0);
			glScalef(size, size, 1);
			glColor3ub(110, 95, 73);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

			DrawCellTexture(texture);
			DrawFrame();
		glPopMatrix();
	DisableCellGlState();
}

void MenuCell::DrawAsTexture(const texture_t texture, std::function<void()> drawingEffectFunction) {
	EnableCellGlState();
		glPushMatrix();
			glTranslatef(offset.x, offset.y, 0);

			glPushMatrix();
				glScalef(size, size, 1);
				glColor3f(1, 1, 1);

				glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, texture);
					glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
				glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			drawingEffectFunction();
		glPopMatrix();
	DisableCellGlState();
}

