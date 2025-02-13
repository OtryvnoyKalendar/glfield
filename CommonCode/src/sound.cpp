#include "sound.h"
#include "gameconf.h"

void SoundInMemory::PlayNext() {
	soundObjects[currentSound].play();
	currentSound += 1;
	if(currentSound >= soundsNum)
		currentSound = 0;
}

SoundInMemory::SoundInMemory(int _soundsNum)
	: soundsNum(_soundsNum), currentSound(0) {
	if(_soundsNum <= 0) {
		printf("invalid soundsNum");
		exit(1);
	}
	soundObjects.resize(_soundsNum+1, sf::Sound(soundBuffer));
}

void SoundInMemory::SetSoundObjects() {
	for(int i = 0; i < soundsNum; i++)
		soundObjects[i].setBuffer(soundBuffer);
}

AudioId AudioManager::LoadSound(const std::string& soundFilename, int _soundsNum) {
	const AudioId size = array.size();
	array.push_back(SoundInMemory(_soundsNum));

	std::string currentPath = GetSoundsPath() + soundFilename;
	if(!array[size].soundBuffer.loadFromFile(currentPath.c_str()))
		exit(1);

	isCompleteUpload = false;
	return size;
}

void AudioManager::CompleteUpload() {
	for(SoundInMemory& i : array)
		i.SetSoundObjects();

	isCompleteUpload = true;
}

AudioId AudioManager::LoadMusic(const std::string& musicFilename) {
	const AudioId size = musicsNum;
	musicsNum += 1;
	if(musicsNum > musicsNumMax) {
		printf("limit on the number of music objects uploaded = %ld\n", musicsNumMax);
		exit(1);
	}

	std::string currentPath = GetMusicPath() + musicFilename;
	if(!musics[size].openFromFile(currentPath.c_str()))
		exit(1);

	return size;
}

void AudioManager::CheckSoundId(AudioId id) {
	if(id >= array.size()) {
		printf("invalid audio id\n");
		exit(1);
	}
	else if(!isCompleteUpload) {
		CompleteUpload();
	}
}

void AudioManager::CheckMusicId(AudioId id) {
	if(id >= musics.size()) {
		printf("invalid audio id\n");
		exit(1);
	}
}

void AudioManager::PlayMusic(AudioId id) {
	CheckMusicId(id);
	musics[id].play();
}

void AudioManager::StopMusic(AudioId id) {
	CheckMusicId(id);
	musics[id].stop();
}

void AudioManager::PlaySound(AudioId id) {
	CheckSoundId(id);
	array[id].PlayNext();
}

