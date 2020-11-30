#pragma once
const int g_DuckArraySize{ 10 };
const int g_PopupNamesArraySize{ 2 };



class MainGame
{
public:
	void Start();
	void Draw();
	void Update(float elapsedSec);
	void SpawnDuck();
	void reset();

	float g_TimerValue{ 0.3f };
	const float g_TrackHeight{ 100 };
private:
	//Vars
	Grid m_MultiplierGrid{ 1280.0f/2 , 720.0f/2 + 40, 100, 10, 10, 4, 40 };
	int* m_MultiplierGridArray{};

	struct Duck {
		int value;
		float yOffset;
		Point2f position;
	};
	Duck m_DuckArray[g_DuckArraySize]{  };

	float m_DuckSpeed{494.0f}; // 2 sec from Spawn to click
	float m_DuckWidth{};

	//TrackVars
	const int m_GridSize{ 10 };
	float m_CellSize{};

	const Point2f m_TrackPosition{ 60, 25.0f };
	const float m_TrackLineThickness{ 8 };
	const float m_TrackBorder{ 60 };
	const float m_TrackWidth{ 1280 - (2 * m_TrackBorder) };

	//FeedbackVars
	float m_PosRadius{ (m_CellSize * 8.0f / 10) / 2 };
	bool m_PosFeedback{false};
	float m_PosFeedbackTimerValue{ 0.2f };
	float m_PosFeedbackTimer{ m_PosFeedbackTimerValue };
	float m_PosAccumulatedTime{};

	float m_NegRadius{ (m_CellSize * 8.0f / 10) / 2 };
	bool m_NegFeedback{ false };
	float m_NegFeedbackTimerValue{ 0.2f };
	float m_NegFeedbackTimer{ m_PosFeedbackTimerValue };
	float m_NegAccumulatedTime{};

	float m_TotalLevelTime{};
	bool m_FinishedSong{};

	//UpdateFunctions
	void UpdateDucks(float elapsedSec);
	void CheckDucks();
	void CheckInput();
	void CheckMouseInput();

	//DrawFunctions
	void DrawDucks(const Duck array[]);
	void DrawBeatCatcher(Point2f startPos, float width, float height, int gridSize);
	void DrawTrack();
	void DrawHealth();
	void DrawScore();
	void DrawTimeBar();

	//Health&Score
	int m_Score{};
	int m_Health{ 100 };
	void AddHealth(int amount);
	void AddScore(int amount);

	//Popups
	Point2f m_PopupPosition{};
	Texture m_CurrPopupTexture{};
	int m_ConsequtiveGoodHits{ 0 };
	int m_ConsequtiveHitsForPopup{ 5 };
	std::string m_PopupNames[g_PopupNamesArraySize]{ "wow.png", "test.png" };
	float m_PopupSize{100};
	float m_MinPopupSize{100};
	float m_MaxPopupSize{500};
	float m_PopupAccumulatedTime{0};
	float m_PopupTimer{0};
	float m_PopupTimerValue{0.5f};
	bool m_IsPopupActive{};

	//Multiplier
	int m_Multiplier{1};
	int m_MaxMultiplierFactor{99};
	float m_MultiplierCooldown{5.0f};
	float m_MultiplierTimer{ m_MultiplierCooldown };

	Point2f m_MultiplierBubblePoint{0,0};
	float m_MultiplierBubbleTimer{};
	float m_MultiplierBubbleRadius{};
	float m_totalDucks{};
	float m_ducksHit{};
	bool m_IsMultiplierBubbleShowing{};

	void AddMultiplier();
	void UpdateMultiplier(float elapsedSec);
	void DrawMultiplier();
	void UpdateMultiplierBubble(float elapsedSec);
	void DrawMultiplierBubble();

	void DrawBackgroundOverDucks();

	void UpdatePositiveFeedback(float elapsedSec);
	void DrawPositiveFeedback();
	void UpdateNegativeFeedback(float elapsedSec);
	void DrawNegativeFeedback();
	void UpdatePopups(float elapsedSec);
	void DrawPopups();

	//UtilFunctions
	float GetDistance(const Point2f& point1, const Point2f& point2);
	float GetRand(float min, float max);

};

class MainMenu
{
public:
	void Draw();
	void Update(float elapsedSec);
private:
	void HandleInput(std::string& name);
};

