#pragma once

#include <vector>
#include <array>
#include <string>

#include "glcore.hpp"

using AudioId = unsigned long int;

class SoundInMemory {
public:
	sf::SoundBuffer soundBuffer;

	SoundInMemory(int _soundsNum);
	void PlayNext();
	void SetSoundObjects();
private:
	int soundsNum;
	int currentSound;
	std::vector<sf::Sound> soundObjects;
};

class AudioManager {
public:
	AudioId LoadSound(const std::string& soundFilename, int _soundsNum);
	void PlaySound(AudioId id);
	void CompleteUpload();

	AudioId LoadMusic(const std::string& musicFilename);
	void PlayMusic(AudioId id);
	void StopMusic(AudioId id);
private:
	bool isCompleteUpload{false};
	std::vector<SoundInMemory> array;

	AudioId musicsNum{0};
	static const AudioId musicsNumMax{100};
	std::array<sf::Music, musicsNumMax> musics;

	void CheckMusicId(AudioId id);
	void CheckSoundId(AudioId id);
};

extern AudioManager audio;

