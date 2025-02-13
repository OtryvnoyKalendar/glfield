#include "sound.h"
#include "gameconf.h"

AudioId sndLaserShoot;
AudioId sndPaper;
AudioId mscRelax;

void InitSounds() {
	sndLaserShoot = audio.LoadSound("laser_shoot.wav", 10);
	sndPaper = audio.LoadSound("listyi_bumagu.wav", 10);

	mscRelax = audio.LoadMusic("golden-hours.wav");
}

