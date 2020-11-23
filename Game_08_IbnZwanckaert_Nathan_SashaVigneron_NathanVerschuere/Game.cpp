#include "pch.h"
#include "Game.h" 

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	InitializeGameAssets();
	int score{ 1000 };
	if (AddScore(score))std::cout << "HighScore\n";
	else std::cout << "Top 5!\n";
}

void Draw()
{
	ClearBackground();
	switch (g_Scene)
	{
	case 0:
		g_MainGame.Draw();
		break;
	case 1:
		g_MainMenu.Draw();
		break;
	}
}

void Update(float elapsedSec)
{

}

void End()
{
	// free game resources here
}
#pragma endregion gameFunctions

#pragma region ownDefinitions

#pragma endregion ownDefinitions