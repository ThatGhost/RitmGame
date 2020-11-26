#include "pch.h"
#include "MainGame.h"

extern float g_WindowHeight;
extern float g_WindowWidth;
extern InputS Input;

using namespace utils;
using namespace UI;

#pragma region Game
void MainGame::Start() 
{
	
}

void MainGame::Draw() 
{
	DrawTexture(*GetTexture("Background.png"),Point2f(0,0));

	DrawTrack();
	DrawDucks(m_DuckArray);
	DrawHealth();
	DrawScore();
	DrawPositiveFeedback();
	DrawNegativeFeedback();

}


void MainGame::End() 
{

}

//int timerTimes{}; // DEBUG
void MainGame::Update(float elapsedSec) 
{
	m_TotalLevelTime += elapsedSec;
	if (!m_FinishedSong && m_TotalLevelTime >= GetNextDuck()) {
		SpawnDuck();
		m_FinishedSong = NextStamp();
	}

	m_Timer -= elapsedSec;
	if (m_Timer <= 0)
	{
		//timerTimes++;
		UpdateDucks();
		CheckDucks();
		m_Timer = g_TimerValue;
		//if (timerTimes == 3)	// DEBUG
		//{						// DEBUG
		//	SpawnDuck();		// DEBUG
		//	timerTimes = 0;		// DEBUG
		//}						// DEBUG
	}

	CheckInput();
	UpdatePositiveFeedback(elapsedSec);
	UpdateNegativeFeedback(elapsedSec);
}
void MainGame::SpawnDuck()
{
	m_DuckArray[g_DuckArraySize - 1].value = 1;
	m_DuckArray[g_DuckArraySize - 1].color = Color4f(GetRand(0.0f, 1.0f), GetRand(0.0f, 1.0f), GetRand(0.0f, 1.0f), 0.5f);
	m_DuckArray[g_DuckArraySize - 1].offset = Point2f(float(rand() % 20 - 5), float(rand() % 20 - 5));
}

//private functions
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
	if (m_DuckArray[1].value == 1)
	{
		m_DuckArray[1].value = 0;
		PlaySoundEffect("place.wav");
		AddHealth(-5);
		m_NegFeedback = true;
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
	const float xOffset{ (m_CellSize - duckSize) / 2 };

	for (int i = 2; i < g_DuckArraySize; i++)
	{
		if (array[i].value == 1)
		{

			Rectf duckRect{ m_TrackPosition.x + xOffset + (i * m_CellSize) + m_DuckArray[g_DuckArraySize - 1].offset.x,
							m_TrackPosition.y - (m_TrackLineThickness / 2) + m_DuckArray[g_DuckArraySize - 1].offset.y,
							float(m_CellSize * 9 / 10),
							float(m_CellSize * 9 / 10) };
			DrawTexture(*GetTexture("Duck2.png"), duckRect);
			//SetColor(array[i].color);
			//FillRect(duckRect);
		}
		SetColor(0.3f, 0.2f, 0.3f);
	}
}

void MainGame::DrawHealth()
{
	float border{ 10 };
	float width{ 300 };
	float height{ 25 };
	float insideBorder{ 5 };
	float insideWidth{ (width - (2 * insideBorder)) };
	float insideHeight{ height - (2 * insideBorder) };

	Rectf outsideBar{ border, g_WindowHeight - height - border, width, height };
	Rectf insideBar{ border + insideBorder, g_WindowHeight - height - border + insideBorder, insideWidth, insideHeight };
	Rectf healthBar{ border + insideBorder, g_WindowHeight - height - border + insideBorder, insideWidth * (m_Health / 100.0f), insideHeight };

	SetColor(0.3f, 0.2f, 0.3f);
	FillRect(outsideBar);
	SetColor(0.4f, 0.3f, 0.4f);
	FillRect(insideBar);
	SetColor(0.8f, 0.5f, 0.4f);
	FillRect(healthBar);
}

void MainGame::DrawScore()
{
	float scale{ 50 };
	float offset{ scale / 2 };
	int nrChars{};
	std::string scoreString{ std::to_string(m_Score) };
	for (int i = 0; i < scoreString.length(); i++)
	{
		nrChars++;
	}
	FillText(std::to_string(m_Score), Point2f((g_WindowWidth / 2) - (nrChars * offset), g_WindowHeight - 100), scale);
}

void MainGame::CheckInput() 
{
	if (Input.keyUp == SDLK_z)
	{
		//std::cout << "Z was pressed\n";
		if (m_DuckArray[2].value == 1) 
		{
			m_DuckArray[2].value = 0; // Remove Duck
			m_PosFeedback = true;
			PlaySoundEffect("beat.wav");
			AddScore(rand() % 51);
			AddHealth(3);
		}
		else
		{
			//std::cout << "No duck there!\n";
			m_NegFeedback = true;
			AddHealth(-5);
			PlaySoundEffect("place.wav");
		}
	}
}

	#pragma region Health&Score

	void MainGame::AddHealth(int amount) 
	{
		m_Health += amount;
		if (m_Health < 0) m_Health = 0;
		if (m_Health > 100) m_Health = 100;
	}
	void MainGame::AddScore(int amount)
	{
		m_Score += amount;
	}

	#pragma endregion

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

void MainGame::UpdatePositiveFeedback(float elapsedSec) 
{
	if (m_PosFeedback) 
	{
		m_PosAccumulatedTime += elapsedSec;
		m_PosFeedbackTimer -= elapsedSec;
		m_PosRadius = (m_CellSize * ((8.0f + (4.0f * (m_PosAccumulatedTime / m_PosFeedbackTimerValue))) / 10)) / 2 ;
		// 8/10 of cell + 4/10 * m_accumulated/m_feedback -> range [ 8/10 cell , 12/10 cell ]

		if (m_PosFeedbackTimer <= 0)
		{
			m_PosFeedbackTimer = m_PosFeedbackTimerValue;
			m_PosAccumulatedTime = 0;
			m_PosFeedback = false;
		}
	}
		

}

void MainGame::DrawPositiveFeedback() 
{
	if (m_PosFeedback) 
	{
		const float xOffset{ m_CellSize / 2.0f };
		const float yOffset{ m_CellSize / 2.0f };
		SetColor(0.6f, 0.7f, 1, 0.5f);
		FillEllipse(m_TrackPosition.x + xOffset + (2 * m_CellSize), m_TrackPosition.y + yOffset - (m_TrackLineThickness), m_PosRadius, m_PosRadius);
	}
}

void MainGame::UpdateNegativeFeedback(float elapsedSec)
{
	if (m_NegFeedback)
	{
		m_NegAccumulatedTime += elapsedSec;
		m_NegFeedbackTimer -= elapsedSec;
		m_NegRadius = (m_CellSize * ((8.0f + (4.0f * (m_NegAccumulatedTime / m_NegFeedbackTimerValue))) / 10)) / 2;
		// 8/10 of cell + 4/10 * m_accumulated/m_feedback -> range [ 8/10 cell , 12/10 cell ]

		if (m_NegFeedbackTimer <= 0)
		{
			m_NegFeedbackTimer = m_NegFeedbackTimerValue;
			m_NegAccumulatedTime = 0;
			m_NegFeedback = false;
		}
	}


}

void MainGame::DrawNegativeFeedback()
{
	if (m_NegFeedback)
	{
		const float xOffset{ m_CellSize / 2.0f };
		const float yOffset{ m_CellSize / 2.0f };
		SetColor(1, 0.5f, 0.5f, 0.5f);
		FillEllipse(m_TrackPosition.x + xOffset + (2 * m_CellSize), m_TrackPosition.y + yOffset - (m_TrackLineThickness), m_NegRadius, m_NegRadius);
	}
}
#pragma endregion Menu

#pragma region Menu
void MainMenu::Start() {

}

void MainMenu::Draw() {
	DrawTexture(*GetTexture("BackgroundMenu.png"), Point2f(0, 0));
	//std::cout << (int)GetTexture("Background.png")->height << '\n';
	int widthButton{ 800 }, heightButton{ (int)GetTexture("Background.png")->height / 6 }, margin{30};
	for (size_t i = 0; i < 3; i++)
	{
		widthButton -= 80;
		Point2f posButton{ g_WindowWidth - widthButton , 
			g_WindowHeight / 2 - margin - heightButton / 2 - heightButton + (heightButton + margin) * i  -100};
		std::string name{};
		if (i == 0) {
			name = "StillDreaming.png";
			if(UIButton(posButton, GetTexture(name), 70))HandleInput(name);
		}
		else if (i == 1) {
			name = "Towerz.png";
			if (UIButton(posButton, GetTexture(name), 70))HandleInput(name);
		}
		else {
			name = "Tenno.png";
			if (UIButton(posButton, GetTexture(name), 70))HandleInput(name);
		}
	}
}

void MainMenu::End() {

}

void MainMenu::Update(float elapsedSec) 
{

}

void MainMenu::HandleInput(std::string& name) {
	size_t lastPlace{ (size_t)name.length()};
	name.resize(lastPlace-3);
	StartLevel(name);
}
#pragma endregion Menu