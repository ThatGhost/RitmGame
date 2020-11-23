#include "pch.h"
#include "Game.h"

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	
}

void Draw()
{
	ClearBackground();
	switch (g_Scene)
	{
	case 0:
		g_MenuClass.Draw();
		break;
	case 1:
		g_GameClass.Draw();
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