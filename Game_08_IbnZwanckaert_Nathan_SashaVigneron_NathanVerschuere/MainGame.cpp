#include "pch.h"
#include "MainGame.h"
extern float g_WindowHeight;
extern float g_WindowWidth;
using namespace utils;
using namespace UI;

#pragma region Game
void MainGame::Start() {
	
}

void MainGame::Draw() {
	DrawTexture(*GetTexture("Background.png"),Point2f(0,0));

	SetColor(0.3f, 0.2f, 0.3f); // Purple Color
	Point2f rectPosition{ 60, 25 };

//<<<<<<< Updated upstream
//=======
	if (m_DuckArray[1] == 1) 
	{
		m_DuckArray[1] = 0;
		PlaySoundEffect("place.wav");
		SpawnDuck();
		// AND PUNISH PLAYER
	}
//>>>>>>> Stashed changes


	float duckSize{ 250 };
	Point2f duckPosition{ 10, -50 };
	Rectf duckRect{ duckPosition.x, duckPosition.y, duckSize, duckSize }; // x, y, scaleX, scaleY

	//Change later <- edges are shit
	DrawRect(rectPosition.x, rectPosition.y, 1280 - (2 * rectPosition.x), 100, 8);
	DrawRect(rectPosition.x + 200, rectPosition.y, 100, 100, 8);

	DrawTexture(*GetTexture("Duck1.png"), duckRect);

	DrawDucks(g_DuckArray);

}

void MainGame::SpawnDuck(const Point2f& spawnPosition)
{

}

void MainGame::DrawDucks(const int array[])
{
	float duckSize{ 100 };

	for (int i = 0; i < duckArraySize; i++)
	{
		Rectf duckRect{ float(array[i]), 25.0f, duckSize, duckSize };
		DrawTexture(*GetTexture("Duck2.png"), duckRect);
	}
}


void MainGame::End() {

//<<<<<<< Updated upstream
//=======
void MainGame::Update(float elapsedSec) 
{
	g_Timer -= elapsedSec;
	if (g_Timer <= 0)
	{
		UpdateDucks();
		CheckDucks();
		g_Timer = g_TimerValue;
	}
//>>>>>>> Stashed changes
}

void MainGame::Update(float elapsedSec) {

}
#pragma endregion Menu

#pragma region Menu
void MainMenu::Start() {

}

void MainMenu::Draw() {
	DrawTexture(*GetTexture("Background.png"), Point2f(0, 0));

}

void MainMenu::End() {

}

void MainMenu::Update(float elapsedSec) {

}
#pragma endregion Menu