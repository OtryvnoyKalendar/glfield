#include <iostream>
#include <fstream> // for std::ifstream
#undef NDEBUG
#include <cassert>

#include "gameconf.h"

std::string resourcePath{};
bool isResourcePathLoaded{false};

void CheckResourcePath() {
	assert(isResourcePathLoaded && "The path to the resources is not loaded");

	if(resourcePath.back() != '/')
		resourcePath += '/';
}

std::string GetResourcesPath() {
	CheckResourcePath();
	return resourcePath;
}

std::string GetSoundsPath() {
	return GetResourcesPath() + "sounds/";
}

std::string GetTexturesPath() {
	return GetResourcesPath() + "textures/";
}

std::string GetMusicPath() {
	return GetResourcesPath() + "music/";
}

void LoadConfigInfo() {
	resourcePath = "";
	
	std::ifstream file("game.conf");
	assert(file && "Error reading game.conf");

	const char* openMessage = "\nLoad resource directory: ";
	std::string line;
	getline(file, line); resourcePath += line;
	while(getline(file, line))
		std::cout << "unknown settings: "<< line << std::endl;
	std::cout << openMessage << resourcePath << std::endl;

	file.close();

	isResourcePathLoaded = true;
}

