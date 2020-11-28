#include "pch.h"
#include "MainGame.h"

extern float g_WindowHeight;
extern float g_WindowWidth;
extern InputS Input;
extern INT8 g_Scene;

using namespace utils;
using namespace UI;

#pragma region Game
void MainGame::reset() {
	for (size_t i = 0; i < g_DuckArraySize; i++)
	{
		m_DuckArray[i].value = 0;
	}
	m_Score = 0;
	m_Multiplier = 1;
	m_TotalLevelTime = 0;
	m_FinishedSong = false;
	m_Health = 100;
	m_totalDucks = 0;
	m_ducksHit = 0;
}

void MainGame::Draw() 
{
	DrawTexture(*GetTexture("Background.png"), Point2f(0, 0));
	DrawDucks(m_DuckArray);
	DrawBackgroundOverDucks();
	DrawTimeBar();

	DrawTrack();
	DrawHealth();
	DrawScore();
	DrawPositiveFeedback();
	DrawNegativeFeedback();
	DrawMultiplier();
	DrawMultiplierBubble();
	DrawPopups();
}

void MainGame::Update(float elapsedSec) 
{
	m_TotalLevelTime += elapsedSec;
	//std::cout << m_TotalLevelTime << '\n';
	if (!m_FinishedSong && m_TotalLevelTime >= GetNextDuck()) {
		SpawnDuck();
		m_totalDucks++;
		if(NextStamp())m_FinishedSong = true;
	}

	if (m_TotalLevelTime > GetEndSong())
	{
		g_Scene = 2;
		EndSong(m_Score, float(m_ducksHit / m_totalDucks), AddEndScore(m_Score));
	}

	UpdateDucks(elapsedSec);
	CheckDucks();

	CheckInput();
	CheckMouseInput();
	UpdatePositiveFeedback(elapsedSec);
	UpdateNegativeFeedback(elapsedSec);
	UpdateMultiplier(elapsedSec);
	UpdateMultiplierBubble(elapsedSec);
	UpdatePopups(elapsedSec);
}

void MainGame::SpawnDuck()
{

	int duckInt{};
	for (int i = 0; i < g_DuckArraySize; i++)
	{
		if (m_DuckArray[i].value == 0) 
		{
			duckInt = i;
			break;
		}
	}

	m_DuckArray[duckInt].value = 1;
	m_DuckArray[g_DuckArraySize - 1].yOffset = float(rand() % 20 - 5);
	m_DuckArray[duckInt].position = Point2f(g_WindowWidth, m_TrackPosition.y - (m_TrackLineThickness / 2));
}

//private functions
void MainGame::UpdateDucks(float elapsedSec)
{
	for (int i = 0; i < g_DuckArraySize; i++)
	{
		if (m_DuckArray[i].value == 1) 
		{
			m_DuckArray[i].position.x -= m_DuckSpeed * elapsedSec;
		}
	}
}

void MainGame::CheckDucks()
{
	bool wasDuckInPlace{ false };
	int duckInt{};
	for (int i = 0; i < g_DuckArraySize; i++)
	{
		if (m_DuckArray[i].position.x + (m_DuckWidth / 4) < (m_TrackPosition.x + (m_CellSize * 2))) 
		{
			if (m_DuckArray[i].value == 1) 
			{
				wasDuckInPlace = true;
				duckInt = i;
			}
		}
	}

	if (wasDuckInPlace)
	{
		m_DuckArray[duckInt].value = 0;
		PlaySoundEffect("place.wav");
		AddHealth(-15);
		m_Multiplier = 1;
		m_ConsequtiveGoodHits = 0;
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
	m_DuckWidth = float(m_CellSize * 9 / 10);

	bool wasDuckInPlace{};
	for (int i = 0; i < g_DuckArraySize; i++)
	{
		if (m_DuckArray[i].position.x >= (m_TrackPosition.x + (m_CellSize * 2) - (m_DuckWidth / 4))
			&& m_DuckArray[i].position.x <= (m_TrackPosition.x + (m_CellSize * 3)) + (m_DuckWidth / 4))
		{
			if (m_DuckArray[i].value == 1)
			{
				wasDuckInPlace = true;
			}
		}
	}

	(wasDuckInPlace) ? SetColor(0.7f, 0.5f, 0.1f) : SetColor(0.5f, 0.2f, 0.3f);
	DrawRect(startPos.x + (m_CellSize * 2), startPos.y, m_CellSize, g_TrackHeight, m_TrackLineThickness);
	SetColor(0.3f, 0.2f, 0.3f);
}

void MainGame::DrawDucks(const Duck array[])
{
	for (int i = 0; i < g_DuckArraySize; i++)
	{
		if (array[i].value == 1)
		{
			Rectf duckRect{ m_DuckArray[i].position.x,
							m_DuckArray[i].position.y - (m_TrackLineThickness / 2) + m_DuckArray[i].yOffset,
							m_DuckWidth,
							m_DuckWidth };
			DrawTexture(*GetTexture("Duck2.png"), duckRect);
		}
		SetColor(0.3f, 0.2f, 0.3f);
	}
}

void MainGame::DrawTimeBar() 
{
	float width{ (m_TrackWidth + (m_TrackLineThickness/2)) };
	Rectf timeBar{ m_TrackPosition.x, m_TrackPosition.y + g_TrackHeight + 20, width - (width * (m_TotalLevelTime / GetEndSong())), 15};

	SetColor(0.3f, 0.2f, 0.3f);
	FillRect(timeBar);
}

void MainGame::CheckInput() 
{
	if (Input.keyUp == SDLK_z)
	{
		bool wasDuckInPlace{ false };
		int duckInt{};
		for (int i = 0; i < g_DuckArraySize; i++)
		{
			if (m_DuckArray[i].position.x >= (m_TrackPosition.x + (m_CellSize * 2) - (m_DuckWidth / 4))
				&& m_DuckArray[i].position.x <= (m_TrackPosition.x + (m_CellSize * 3)) + (m_DuckWidth / 4))
			{
				if (m_DuckArray[i].value == 1) 
				{
					wasDuckInPlace = true;
					duckInt = i;
				}
			}
		}

		if (wasDuckInPlace) 
		{
			m_DuckArray[duckInt].value = 0;
			m_PosFeedback = true;
			PlaySoundEffect("beat.wav");
			AddScore(rand() % 51);
			m_ConsequtiveGoodHits++;
			m_MultiplierTimer = m_MultiplierCooldown;
			AddHealth(3);
			m_ducksHit++;
		}
		else 
		{
			m_NegFeedback = true;
			m_ConsequtiveGoodHits = 0;
			AddHealth(-5);
			m_Multiplier = 1;
			PlaySoundEffect("place.wav");
		}
	}
}

void MainGame::CheckMouseInput() 
{
	if (Input.ClickUp == Input.MB1) 
	{
		if (GetDistance(Input.mousePos, m_MultiplierBubblePoint) <= m_MultiplierBubbleRadius && m_IsMultiplierBubbleShowing)
		{
			m_IsMultiplierBubbleShowing = false;
			AddMultiplier();
		}
	}
}

void MainGame::DrawBackgroundOverDucks() 
{
	Rectf srcRect{ m_TrackPosition.x + (m_CellSize * 10),g_WindowHeight - m_TrackPosition.y, m_CellSize, g_TrackHeight };
	Rectf destRect{ m_TrackPosition.x + (m_CellSize * 10), m_TrackPosition.y, m_CellSize, g_TrackHeight };

	DrawTexture(*GetTexture("Background.png"), destRect, srcRect);
}

	#pragma region Health&Score
	void MainGame::AddHealth(int amount) 
	{
		m_Health += amount;
		if (m_Health <= 0) {
			EndSong(m_Score,float(m_ducksHit/m_totalDucks));			
			g_Scene = 3;
			m_Health = 0;
		}
		if (m_Health > 100) m_Health = 100;
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

	void MainGame::AddScore(int amount)
	{
		m_Score += amount * m_Multiplier;
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
		FillText(std::to_string(m_Score), Point2f((g_WindowWidth / 2) - (nrChars * offset), g_WindowHeight - 100), int(scale));
	}

	void MainGame::AddMultiplier() 
	{
		m_Multiplier *= 2;
		if (m_Multiplier > m_MaxMultiplierFactor) m_Multiplier = m_MaxMultiplierFactor;
		m_MultiplierTimer = m_MultiplierCooldown;
	}
	void MainGame::UpdateMultiplier(float elapsedSec) 
	{
		m_MultiplierTimer -= elapsedSec;

		if (m_MultiplierTimer <= 0)
		{
			m_MultiplierTimer = m_MultiplierCooldown;
			m_Multiplier = 1;
		}
	}
	void MainGame::DrawMultiplier() 
	{
		float scale{ 50 };
		float offset{ scale / 2 };
		int nrChars{};
		std::string scoreString{ std::to_string(m_Multiplier) };
		for (int i = 0; i < scoreString.length(); i++)
		{
			nrChars++;
		}
		FillText("x" + std::to_string(m_Multiplier), Point2f((g_WindowWidth - 100) - (nrChars * offset), g_WindowHeight - 100), int(scale));
	}
	void MainGame::UpdateMultiplierBubble(float elapsedSec)
	{
		m_MultiplierBubbleTimer -= elapsedSec;
		if (m_MultiplierBubbleTimer <= 0)
		{
			if (m_IsMultiplierBubbleShowing)
			{
				m_IsMultiplierBubbleShowing = false;
				m_MultiplierBubbleTimer = float(rand() % 10 + 2);
			}
			else
			{
				float offset{ 100 };
				m_MultiplierBubblePoint.x = rand() % int(g_WindowWidth - (2 * m_MultiplierBubbleRadius + 2 * offset)) + m_MultiplierBubbleRadius + offset;
				m_MultiplierBubblePoint.y = rand() % int(g_WindowHeight - (2 * m_MultiplierBubbleRadius + 2 * offset) - (m_TrackPosition.x + m_CellSize)) + m_MultiplierBubbleRadius + offset + (m_TrackPosition.x + m_CellSize);
				m_MultiplierBubbleRadius = float(rand() % 50 + 10);
				m_IsMultiplierBubbleShowing = true;
				m_MultiplierBubbleTimer = float(rand() % 5 + 2);

			}
		}
	}
	void MainGame::DrawMultiplierBubble()
	{
		if (m_IsMultiplierBubbleShowing)
		{
			SetColor(0.3f, 0.8f, 0.8f, 0.5f);
			FillEllipse(m_MultiplierBubblePoint, m_MultiplierBubbleRadius, m_MultiplierBubbleRadius);
			int scale{ int(m_MultiplierBubbleRadius * 0.8f) };
			std::string string{ "x2" };
			float offset{ scale / 2.0f };
			int nrChars{};
			for (int i = 0; i < string.length(); i++)
			{
				nrChars++;
			}
			Point2f textPos{ m_MultiplierBubblePoint.x - nrChars * offset, m_MultiplierBubblePoint.y - offset };
			FillText(string, textPos, scale);
		}
	}
	#pragma endregion
	#pragma region Utils
	float MainGame::GetDistance(const Point2f& point1, const Point2f& point2)
	{
		float result{};
		result = sqrtf(powf(point2.x - point1.x, 2) + powf(point2.y - point1.y, 2));
		return result;
	}

	float MainGame::GetRand(float min, float max)
	{
		float result{};

		result = ((rand() % int((max - min) * 100)) / 100.0f) + min;

		return result;
	}
	#pragma endregion
	#pragma region feedback
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

	void MainGame::UpdatePopups(float elapsedSec) 
	{
		if (m_IsPopupActive)
		{
			m_PopupSize = (m_MaxPopupSize -m_MinPopupSize) * (m_PopupAccumulatedTime / m_PopupTimerValue) + m_MinPopupSize;
			m_PopupAccumulatedTime += elapsedSec;
			m_PopupTimer -= elapsedSec;
			
			if (m_PopupTimer <= 0)
			{
				m_IsPopupActive = false;
				m_PopupTimer = m_PopupTimerValue;
				m_PopupAccumulatedTime = 0;
			}
		}
		else 
		{
			if (m_ConsequtiveGoodHits >= m_ConsequtiveHitsForPopup) 
			{
				m_ConsequtiveGoodHits = 0;
				m_ConsequtiveHitsForPopup = rand() % 5 + 3;

				float offset{ 100 };
				m_CurrPopupTexture = *GetTexture(m_PopupNames[rand() % g_PopupNamesArraySize]);
				float aspectRatioY{ m_CurrPopupTexture.height / m_CurrPopupTexture.width };
				m_PopupSize = 100;
				m_PopupPosition.x = rand() % int(g_WindowWidth - (m_MaxPopupSize + 2 * offset)) + offset;
				m_PopupPosition.y = rand() % int(g_WindowHeight - (m_MaxPopupSize * aspectRatioY + 2 * offset + m_TrackPosition.x + m_CellSize)) + offset + m_TrackPosition.x + m_CellSize;
				m_IsPopupActive = true;
				m_PopupTimer = m_PopupTimerValue;
			}
		}
	}
	void MainGame::DrawPopups() 
	{
		if (m_IsPopupActive)
		{
			float aspectRatioY{ m_CurrPopupTexture.height / m_CurrPopupTexture.width };
			Rectf destRect{ m_PopupPosition.x, m_PopupPosition.y, m_PopupSize, m_PopupSize * aspectRatioY };
			DrawTexture(m_CurrPopupTexture, destRect);
		}
	}
	#pragma endregion

#pragma endregion MainGame

#pragma region Menu
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

		switch (i)
		{
		case 0:
			name = "FloatingAway.png";
			break;
		case 1:
			name = "StillDreaming.png";
			break;
		case 2:
			name = "DarkChocolate.png";
			break;
		}

		if (UIButton(posButton, GetTexture(name), 70))HandleInput(name);
	}
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