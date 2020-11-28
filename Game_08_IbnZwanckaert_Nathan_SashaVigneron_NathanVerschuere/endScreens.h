#pragma once
class WinScreen {
public:
	void Draw();
	void Update(float elapsedSec);
	int score{};
	float percent;
	bool HighScore;
};

class LoseScreen {
public:
	void Draw();
	void Update(float elapsedSec);
	int score;
	float percent;
};

void DrawScreen(bool won, int& score, float& percent, bool highscore = false);

class SettingsMenu {
public: 
	void Draw();
	void Update(float elapsedSec);
	void start();
	INT8 m_Scene{};
private:
	void Return();
	float volume{};
	float DrawSlider(float prev, Point2f pos, Point2f size);
};