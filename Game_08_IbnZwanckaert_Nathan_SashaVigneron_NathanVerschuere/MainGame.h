#pragma once
const int duckArraySize{ 3 };

class MainGame
{

public:
	void Draw();
	void Update(float elapsedSec);
	void Start();
	void End();

	void SpawnDuck(const Point2f& spawnPosition);
private:


	Point2f g_SpawnPoint{ 200,10 };

	int g_DuckArray[duckArraySize]{ (1280 - 150) };

	void DrawDucks(const int array[]);
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

