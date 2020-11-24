#include "pch.h"
#include "MainGame.h"
extern float g_WindowHeight;
extern float g_WindowWidth;

using namespace utils;
using namespace UI;


#pragma region Game
void MainGame::Start() 
{
	SpawnDuck();
	UpdateDucks();
	SpawnDuck();
	UpdateDucks();
	SpawnDuck();
	SpawnDuck();

}

void MainGame::Draw() 
{
	DrawTexture(*GetTexture("Background.png"),Point2f(0,0));

	DrawTrack();
	DrawDucks(m_DuckArray);
}

void MainGame::SpawnDuck()
{
	m_DuckArray[g_DuckArraySize - 1].value = 1;
	m_DuckArray[g_DuckArraySize - 1].color = Color4f(GetRand(0.0f,1.0f), GetRand(0.0f, 1.0f), GetRand(0.0f, 1.0f), 0.5f );
}
void MainGame::UpdateDucks()
{
	for (int i = 0; i < g_DuckArraySize; i++)
	{
		if (i == g_DuckArraySize - 1)
		{
			m_DuckArray[i].value = 0;
			return;
		}
		Swap(m_DuckArray, i, i + 1);
	}
}
void MainGame::CheckDucks() 
{
	if (m_DuckArray[2].value == 1) 
	{
		m_DuckArray[2].value = 0;
		Playsound("place.wav");
		//AND PUNISH PLAYER
	}

}

void MainGame::DrawTrack()
{
	SetColor(0.3f, 0.2f, 0.3f); // Purple Color

	DrawLine(m_TrackPosition.x - (m_TrackLineThickness / 2), m_TrackPosition.y, m_TrackPosition.x + m_TrackWidth + (m_TrackLineThickness / 2), m_TrackPosition.y, m_TrackLineThickness);
	DrawLine(m_TrackPosition.x + m_TrackWidth, m_TrackPosition.y, m_TrackPosition.x + m_TrackWidth, m_TrackPosition.y + g_TrackHeight, m_TrackLineThickness);
	DrawLine(m_TrackPosition.x + m_TrackWidth + (m_TrackLineThickness / 2), m_TrackPosition.y + g_TrackHeight, m_TrackPosition.x - (m_TrackLineThickness / 2), m_TrackPosition.y + g_TrackHeight, m_TrackLineThickness);
	DrawLine(m_TrackPosition.x, m_TrackPosition.y + g_TrackHeight, m_TrackPosition.x, m_TrackPosition.y, m_TrackLineThickness);

	DrawGrid(m_TrackPosition, m_TrackWidth, g_TrackHeight, m_GridSize);

	const float duckSize{ 250 };
	const Point2f duckPosition{ 10, -50 };
	const Rectf duckRect{ duckPosition.x, duckPosition.y, duckSize, duckSize }; // x, y, scaleX, scaleY

	DrawTexture(*GetTexture("Duck1.png"), duckRect);
}
void MainGame::DrawGrid(Point2f startPos, float width, float height, int gridSize)
{
	m_CellSize = width / gridSize;
	for (int i = 3; i < gridSize; i++)
	{
		DrawRect(startPos.x + (m_CellSize * i), startPos.y, m_CellSize, g_TrackHeight, m_TrackLineThickness);
	}
	SetColor(0.5f, 0.2f, 0.3f);
	DrawRect(startPos.x + (m_CellSize * 2), startPos.y, m_CellSize, g_TrackHeight, m_TrackLineThickness);
	SetColor(0.3f, 0.2f, 0.3f);
}
void MainGame::DrawDucks(const Duck array[])
{
	const float duckSize{ 100 };
	const float xOffset{ (m_CellSize - duckSize)/2 };

	for (int i = 2; i < g_DuckArraySize; i++)
	{
		if (array[i].value == 1) 
		{
			Rectf duckRect{ m_TrackPosition.x + xOffset + (i * m_CellSize), m_TrackPosition.y - (m_TrackLineThickness / 2), float(m_CellSize * 9 / 10), float(m_CellSize * 9 / 10) };
			DrawTexture(*GetTexture("Duck2.png"), duckRect);
			SetColor(array[i].color);
			FillRect(duckRect);
		}
	}
}


void MainGame::End() 
{

}

void MainGame::Update(float elapsedSec) 
{
	g_Timer -= elapsedSec;
	if (g_Timer <= 0)
	{
		UpdateDucks();
		CheckDucks();
		g_Timer = g_TimerValue;
	}
}


	#pragma region Utils
	void MainGame::Swap(Duck array[], int idx1, int idx2)
	{
		int tempVar{ array[idx1].value };
		Color4f colorVar{ array[idx1].color };
		array[idx1].value = array[idx2].value;
		array[idx1].color = array[idx2].color;
		array[idx2].value = tempVar;
		array[idx2].color = colorVar;
	}

	float MainGame::GetRand(float min, float max)
	{
		float result{};

		result = ((rand() % int((max - min) * 100)) / 100.0f) + min;

		return result;
	}
	#pragma endregion

#pragma endregion Menu

#pragma region Menu
void MainMenu::Start() {

}

void MainMenu::Draw() {
	DrawTexture(*GetTexture("Background.png"), Point2f(0, 0));

}

void MainMenu::End() {

}

void MainMenu::Update(float elapsedSec) 
{

}
#pragma endregion Menu