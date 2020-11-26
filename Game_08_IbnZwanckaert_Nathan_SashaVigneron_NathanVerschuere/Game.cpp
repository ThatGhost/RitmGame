#include "pch.h"
#include "Game.h"
#include <map>

//Basic game functions
#pragma region gameFunctions											
void Start()
{ 
	SetVolume(0.3f);
	InitializeGameAssets();
	if (g_Scene == 1)g_MainGame.Start();
	else if (g_Scene == 0)g_MainMenu.Start();
}

void Draw()
{
	ClearBackground();
	switch (g_Scene)
	{
	case 1:
		g_MainGame.Draw();
		break;
	case 0:
		g_MainMenu.Draw();
		break;
	}
}

void Update(float elapsedSec)
{
	if(g_Scene == 1)g_MainGame.Update(elapsedSec);
	else if (g_Scene == 0)g_MainMenu.Update(elapsedSec);
}

void End()
{
	if (g_Scene == 1)g_MainGame.End();
	else if (g_Scene==0)g_MainMenu.End();
	DeleteGameAssets();
}
#pragma endregion gameFunctions

#pragma region ownDefinitions

#pragma endregion ownDefinitions