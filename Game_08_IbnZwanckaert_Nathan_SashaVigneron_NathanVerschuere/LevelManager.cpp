#include "pch.h"
#include "LevelManager.h"
#include <irrKlang.h>
using namespace SLUtils;
int g_Idx{1};
std::vector<float> g_TimeStamps;
extern INT8 g_Scene;
extern irrklang::ISoundEngine* engine;
extern LoseScreen g_LoseScreen;
extern WinScreen  g_WinScreen;

float GetNextDuck() {
	float next{};
	next = g_TimeStamps[g_Idx];
	return next;
}

bool NextStamp() {
	bool finished{};
	if(g_Idx < g_TimeStamps.size())g_Idx++;
	if (g_Idx == g_TimeStamps.size() - 1)finished = true;
	return finished;
}

void StartLevel(std::string& name) {
	g_Idx = 1;
	g_TimeStamps.clear();
	g_TimeStamps = ReadFileForfloat("SaveFiles/levels/"+name+"txt");
	name += "mp3";
	PlayMusic(name);
	g_Scene++;
}

void EndSong(int& score, float percent, bool highscore) {
	engine->stopAllSounds();
	g_WinScreen.score = score;
	g_LoseScreen.score = score;
	g_WinScreen.percent = percent;
	g_LoseScreen.percent = percent;
	g_WinScreen.HighScore = highscore;
}

float GetEndSong() {
	return g_TimeStamps[0];
}
