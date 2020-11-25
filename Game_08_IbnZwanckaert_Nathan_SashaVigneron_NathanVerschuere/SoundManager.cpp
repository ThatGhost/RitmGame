#include "pch.h"
#include "SoundManager.h"
#include "SoundStream.h"
#include "SoundEffect.h"
SoundStream music{ "Assets/Audio/bruh.mp3" };
SoundEffect effect{ "Assets/Audio/place.wav" };

void PlayMusic(std::string SoundName) {
	std::string path{ "Assets/Audio/" + SoundName };
	//music = SoundStream(path);
	if (music.IsLoaded()) {
		music.SetVolume(100);
		music.Play(true);
	}
}

void PlaySoundEffect(std::string SoundName) {
	std::string path{ "Assets/Audio/" + SoundName };
	if (effect.IsLoaded()) {
		effect.SetVolume(100);
		effect.Play(true);
	}
}
