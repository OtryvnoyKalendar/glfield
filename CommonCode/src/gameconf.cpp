#include <iostream>
#include <fstream> // for std::ifstream
#include <cstdlib> // for exit

#include "gameconf.h"

std::string resourcePath{};
bool isResourcePathLoaded{false};

void CheckResourcePath() {
	if(!isResourcePathLoaded) {
		printf("the path to the resources is not loaded\n");
		exit(1);
	}
	else {
		if(resourcePath.back() != '/')
			resourcePath += '/';
	}
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
	if(!file) {
        std::cerr << "error reading game.conf" << std::endl;
		exit(1);
	}
	else {
		const char* openMessage = "load resource directory: ";
		
		std::string line;
		getline(file, line); resourcePath += line;
		while(getline(file, line))
			std::cout << "unknown settings: "<< line << std::endl;

		std::cout << openMessage << resourcePath << std::endl;
		file.close();
	}

	isResourcePathLoaded = true;
}

