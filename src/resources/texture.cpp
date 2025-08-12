#include "glcore.hpp"
#include "texture.h"
#include "resource.h"
#include "gameconf.h"

texture_t texUndefined = -1;

texture_t texField;
texture_t texFlowerRed;
texture_t texFlowerYellow;
texture_t texGrass;
texture_t texMushroom;
texture_t texTree;
texture_t texTree2;
texture_t texWood;

texture_t texMortar;
texture_t texPotionEye;
texture_t texPotionLife;
texture_t texPotionSpeed;
texture_t texSkillBlessing;
texture_t texSkillEye;
texture_t texSkillHunger;
texture_t texSkillLightning;
texture_t texSkillSpeed;

void InitTextures() {
	LoadConfigInfo();
	namespace rt = res::texture;
	// rt::set_normal_load(GL_REPEAT, GL_LINEAR); // cool effect
	rt::set_normal_load(GL_REPEAT, GL_NEAREST);

	rt::normal_load("field.png", &texField);
	rt::normal_load("flower_red.png", &texFlowerRed);
	rt::normal_load("flower_yellow.png", &texFlowerYellow);
	rt::normal_load("grass.png", &texGrass);
	rt::normal_load("mushroom.png", &texMushroom);
	rt::normal_load("tree.png", &texTree);
	rt::normal_load("tree2.png", &texTree2);
	rt::normal_load("wood.png", &texWood);

	rt::normal_load("mortar.png", &texMortar);
	rt::normal_load("potion_eye.png", &texPotionEye);
	rt::normal_load("potion_life.png", &texPotionLife);
	rt::normal_load("potion_speed.png", &texPotionSpeed);
	rt::normal_load("skill_blessing.png", &texSkillBlessing);
	rt::normal_load("skill_eye.png", &texSkillEye);
	rt::normal_load("skill_hunger.png", &texSkillHunger);
	rt::normal_load("skill_lightning.png", &texSkillLightning);
	rt::normal_load("skill_speed.png", &texSkillSpeed);
}

