#pragma once
class WinScreen {
public:
	void Draw();
	void Update(float elapsedSec);
	int score;
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

void DrawScreen();

