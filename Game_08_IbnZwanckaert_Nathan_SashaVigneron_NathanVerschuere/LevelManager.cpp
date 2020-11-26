#include "pch.h"
#include "LevelManager.h"
using namespace SLUtils;
int g_Idx{};
std::vector<float> g_TimeStamps;
extern INT8 g_Scene;

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
	g_Idx = 0;
	g_TimeStamps = ReadFileForfloat("SaveFiles/levels/"+name+"txt");
	name += "mp3";
	PlayMusic(name);
	g_Scene++;
}
