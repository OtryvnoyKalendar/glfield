#include "glcore.hpp"
#include "screen.hpp"

GLfloat verticesCursor[] = {
	0,1, 0,-1, -1,0, 1,0,
};

GLuint indexesCursor[] = {0, 1, 2, 3};

// 0.7, 0.7, 0.7, 0.1, 5
void DrawCursor(float r, float g, float b, float a, float cursorSize, float lineWidth) {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glColor4f(r, g, b, a);
		glLineWidth(lineWidth);
		glScalef(cursorSize/screen.aspectRatio, cursorSize, 1);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, verticesCursor);
		glDrawElements(GL_LINES, std::size(indexesCursor), GL_UNSIGNED_INT, indexesCursor);
		glDisableClientState(GL_VERTEX_ARRAY);

		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
}

