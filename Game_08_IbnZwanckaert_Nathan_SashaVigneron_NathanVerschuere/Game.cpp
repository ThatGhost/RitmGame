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
		Menu_Scene();
		break;
	case 1:
		Main_Game();
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
void Menu_Scene() {

}
void Main_Game() {

}

#pragma endregion ownDefinitions