#include "myassert.h"
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
	assert(_soundsNum > 0 && "Invalid soundsNum");
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
	assert(array[size].soundBuffer.loadFromFile(currentPath.c_str()));

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
	assert(musicsNum <= musicsNumMax && "The limit on the number of music objects uploaded has been exceeded");

	std::string currentPath = GetMusicPath() + musicFilename;
	assert(musics[size].openFromFile(currentPath.c_str()));

	return size;
}

void AudioManager::CheckSoundId(AudioId id) {
	assert(id < array.size() && "Invalid audio id");
	if(!isCompleteUpload)
		CompleteUpload();
}

void AudioManager::CheckMusicId(AudioId id) {
	assert(id < musics.size() && "Invalid audio id");
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

