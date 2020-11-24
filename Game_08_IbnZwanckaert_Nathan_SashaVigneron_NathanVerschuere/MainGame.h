#pragma once
const int g_DuckArraySize{ 10 };


class MainGame
{

public:
	void Draw();
	void Update(float elapsedSec);
	void Start();
	void End();

	void SpawnDuck();

	float g_TimerValue{ 0.3f };
	const float g_TrackHeight{ 100 };
private:
	struct Duck {
		int value{ };
		Color4f color{ 0,0,0,0 };
		Point2f offset{ 0,0 };
	};
	Duck m_DuckArray[g_DuckArraySize]{  };

	float m_Timer{ g_TimerValue };

	//TrackVars
	const int m_GridSize{ 10 };
	float m_CellSize{};
	const Point2f m_TrackPosition{ 60, 25.0f };
	const float m_TrackLineThickness{ 8 };
	const float m_TrackBorder{ 60 };
	const float m_TrackWidth{ 1280 - (2 * m_TrackBorder) };

	//UpdateFunctions
	void UpdateDucks();
	void CheckDucks();
	void CheckInput();

	//DrawFunctions
	void DrawDucks(const Duck array[]);
	void DrawGrid(Point2f startPos, float width, float height, int gridSize);
	void DrawTrack();
	void DrawHealth();

	//Health&Score
	int m_Score{};
	int m_Health{ 100 };
	void AddHealth(int amount);
	void AddScore(int amount);

	//UtilFunctions
	float GetRand(float min, float max);
	void Swap(Duck array[], int idx1, int idx2);

};

class MainMenu
{
public:
	void Draw();
	void Update(float elapsedSec);
	void Start();
	void End();
private:
};

