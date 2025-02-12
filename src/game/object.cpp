#include <cstdlib>
#include <iostream>
#include <cmath>

#include "object.h"
#include "map.h"
#include "getrand.h"
#include "camera.h"
#include "vector.h"

GLfloat verticesFlower[] = {
	-0.5,0,0, 0.5,0,0, 0.5,0,1, -0.5,0,1,
	0,-0.5,0, 0,0.5,0, 0,0.5,1, 0,-0.5,1,
};

GLfloat UVFlower[] = {
	0,1, 1,1, 1,0, 0,0, 0,1, 1,1, 1,0, 0,0,
};

GLuint indexesFlower[] = {
	0,1,2, 2,3,0, 4,5,6, 6,7,4,
};

struct Sphere {
	Point center;
	float radius;
};

//float intersect_sphere(Point o, Vector ray, Spheres *sph, Point* hit)
float Object::IsPlayerFocusedOn(float objectRadius) {
	Sphere shpTmp{};
	Sphere* sph = &shpTmp;
	sph->center.x = x;
	sph->center.y = y;
	sph->center.z = z;
	sph->radius = objectRadius;
	float rz = camera.GetZRotRad();
	float rx = camera.GetXRotRad();
	Vector ray = {
		float(
			sin(rx) * cos(rz)
		),
		float(
			cos(rx)
		),
		float(
			sin(rx) * sin(rz)
		),
	};
	//std::cout << "x = " << rx << "\tz = " << rz << std::endl;
	//std::cout << "x = " << ray.x << "\ty = " << ray.y << "\tz = " << ray.z<< std::endl;

	Point hitTmp{};
	Point* hit = &hitTmp;
	Point o = {camera.x, camera.y, camera.z};

	double a = vec_dot(ray, ray);
	double b = 2 * vec_dot(ray, get_vec(sph->center, o));
	double c = vec_dot(get_vec(sph->center, o), get_vec(sph->center, o));
	c -= sph->radius * sph->radius;

	double dt = b * b - 4 * a * c;

	if (dt < 0) {
		return -1.0;
	}
	else {
		double t0 = (-b - sqrt(dt)) / (a * 2);
		if (t0 < 0) {
			return -1.0;
		}

		hit->x = o.x + t0 * ray.x;
		hit->y = o.y + t0 * ray.y;
		hit->z = o.z + t0 * ray.z;

		Vector v = { hit->x - o.x, hit->y - o.y, hit->z - o.z };
		return vec_len(v);
	}
}

bool Object::IsPlayerNearby(float distance) {
	return std::sqrt(std::pow(x - camera.x, 2) + std::pow(y - camera.y, 2) + std::pow(z - camera.z, 2)) < distance;
}

void Objects::DrawSelf() {
	// текстуры и другие настройки уже должны быть включены
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_VERTEX_ARRAY);
	glEnable(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verticesFlower);
	glTexCoordPointer(2, GL_FLOAT, 0, UVFlower);
	
	glNormal3f(0, 0, 1);

	for(int i = 0; i < plantsNum; i++) {
		float selfColorTmp{0.7};
		//if(plants[i].IsPlayerNearby(5.f) && plants[i].IsPlayerFocusedOn(2.f))
		if(plants[i].IsPlayerFocusedOn(2.f) != -1.0)
			selfColorTmp = 0.3;
		glColor3f(selfColorTmp, selfColorTmp, selfColorTmp);

		glBindTexture(GL_TEXTURE_2D, plants[i].tex);
		glPushMatrix();
			glTranslatef(plants[i].x, plants[i].y, plants[i].z);
			glScalef(plants[i].scale, plants[i].scale, plants[i].scale);
			glDrawElements(GL_TRIANGLES, std::size(indexesFlower), GL_UNSIGNED_INT, indexesFlower);
		glPopMatrix();
	}
	
	glDisable(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

void Objects::Init() {
	int grassNum = 2000;
	int mushroomNum = 30;
	int treeNum = 0;

	plantsNum = grassNum + mushroomNum + treeNum;
	plants = new Object[plantsNum];
	if(plants == nullptr) {
		printf("memory allocation error\n");
		exit(1);
	}

	for(int i = 0; i < plantsNum; i++) {
		GLuint newTexture = texGrass;
		float newScale = 1;

		if(i < grassNum) {
			newScale = 0.5 + GetRand(0, 4)*0.1;
			if(GetRand(1, 10) > 9)
				newTexture = texFlowerYellow;
			else if(GetRand(1, 10) > 9)
				newTexture = texFlowerRed;
			else {
				newTexture = texGrass;
				newScale = 0.8 + GetRand(0, 5)*0.1;
			}
		}
		else if(i < grassNum + mushroomNum) {
			newTexture = texMushroom;
			newScale = 0.3 + GetRand(0, 3)*0.1;
		}
		else {
			if(GetRand(1, 10) > 4)
				newTexture = texTree;
			else
				newTexture = texTree2;
			newScale = 4 + GetRand(0, 14);
		}

		plants[i].tex = newTexture;
		plants[i].scale = newScale;
		plants[i].x = GetRand(1, map.width-1);
		plants[i].y = GetRand(1, map.height-1);
		plants[i].z = map.GetHeight(plants[i].x, plants[i].y) - 0.1;
	}
}

void Objects::FreeMemory() {
	if(plants != nullptr) {
		delete [] plants;
		plants = nullptr;
	}
}

Objects::~Objects() {
	FreeMemory();
}

