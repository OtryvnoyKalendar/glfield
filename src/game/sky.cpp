#include "sky.h"
#include "getrand.h"
#include "camera.h"

float alpha{0};
float sunsetValue{0};
float skyBright{0};
GLfloat verticesSun[] = {
	-1,-1,0, 1,-1,0, 1,1,0, -1,1,0,
};

void RotateToCamera() {
	glRotatef(-camera.GetXRot(), 1, 0, 0);
	glRotatef(-camera.GetZRot(), 0, 0, 1);
}

void Sky::DrawSun() {
	glPushMatrix();
		RotateToCamera();
		glRotatef(alpha, 0, 1, 0);
		glTranslatef(0, 0, 20);

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glColor3f(1, 1-sunsetValue*0.8f, 1-sunsetValue);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, verticesSun);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Sky::ApplyLight() {
	glPushMatrix();
		glRotatef(alpha, 0, 1, 0);
		GLfloat position[] = {0, 0, 1, 0};
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		const float lightColorTmp[] = {1+sunsetValue*2, 1, 1, 0};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorTmp);

		const float backgroundLight = sunsetValue*0.1 + 0.05;
		float backgroundLightColorTmp[] = {backgroundLight, backgroundLight, backgroundLight, 0};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, backgroundLightColorTmp);
	glPopMatrix();
}

void Sky::Init() {
	for(int i = 0; i < starsNum; i++) {
		for(int j = 0; j < 3; j++)
			verticesStars[i*3 + j] = GetRand(0,1) == 0 ? GetRand(3, 10) : GetRand(-10, -3);

		starsColorRatio[i] = 0.5f + GetRand(1, 5) * 0.1f;
	}
}

void Sky::DrawBackground() {
	skyBright = 1.f - (abs(alpha) / 180.f);
	glClearColor(0.6f * skyBright, 0.8f * skyBright, 1.0f * skyBright, 0.0f);

	const float sunset{40.f};
	sunsetValue = 90 - abs(alpha);
	sunsetValue = sunset - abs(sunsetValue);
	sunsetValue = sunsetValue < 0 ? 0 : sunsetValue / sunset;
}

void Sky::DrawStars() {
	glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glEnableClientState(GL_VERTEX_ARRAY);
		glPointSize(5);
		const float starColor{0.7};
		glColor4f(starColor,starColor,starColor, 1-skyBright*1.3);

		RotateToCamera();
		glVertexPointer(3, GL_FLOAT, 0, verticesStars);
		glDrawArrays(GL_POINTS, 0, starsNum);
	
		glDisableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
	glPopMatrix();
}

