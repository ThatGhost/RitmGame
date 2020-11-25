#include "pch.h"
#include "SoundManager.h"
#include "irrKlang.h"
#pragma comment(lib, "irrKlang.lib")

irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();

void PlayMusic(const std::string SoundName) {
	std::string path{ "Assets/Audio/" + SoundName };
	engine->play2D(path.c_str());
	//load in level
}

void PlaySoundEffect(const std::string SoundName) {
	std::string path{ "Assets/Audio/" + SoundName };
	engine->play2D(path.c_str());
}

void SetVolume(float volume){
	engine->setSoundVolume(volume);
}
