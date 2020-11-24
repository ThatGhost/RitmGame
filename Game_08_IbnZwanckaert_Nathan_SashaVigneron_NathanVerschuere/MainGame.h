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

	float g_TimerValue{ 0.2f };
	float g_Timer{ g_TimerValue };
	const float g_TrackHeight{ 100 };
private:

	struct Duck {
		int value{ };
		Color4f color{ 0,0,0,0 };
	};

	Duck m_DuckArray[g_DuckArraySize]{  };

	int m_GridSize{10};
	float m_CellSize{};

	const Point2f m_TrackPosition{ 60, 25.0f };
	const float m_TrackLineThickness{ 8 };
	const float m_TrackBorder{ 60 };
	const float m_TrackWidth{ 1280 - (2 * m_TrackBorder) };

	void UpdateDucks();
	void CheckDucks();

	void DrawDucks(const Duck array[]);
	void DrawGrid(Point2f startPos, float width, float height, int gridSize);
	void DrawTrack();

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

