#include "pch.h"
#include "Game.h" 
#include <map>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	InitializeGameAssets();
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
	DeleteGameAssets();
}
#pragma endregion gameFunctions

#pragma region ownDefinitions

#pragma endregion ownDefinitions