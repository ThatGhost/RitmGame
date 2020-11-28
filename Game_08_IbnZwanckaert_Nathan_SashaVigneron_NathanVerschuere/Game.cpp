#include "pch.h"
#include "Game.h"
#include <map>

//Basic game functions
#pragma region gameFunctions											
void Start()
{ 
	SetVolume(0.3f);
	InitializeGameAssets();
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
	case 2:
		g_WinScreen.Draw();
		break;
	case 3:
		g_LoseScreen.Draw();
		break;
	case 4:
		g_Settings.Draw();
		break;
	}
}

void Update(float elapsedSec)
{
	if (Input.keyDown == 'i') {
		g_Settings.m_Scene = g_Scene;
		g_Settings.start();
		g_Scene = 4;
	}

	switch (g_Scene)
	{
	case 1:
		g_MainGame.Update(elapsedSec);
		break;
	case 0:
		g_MainMenu.Update(elapsedSec);
		break;
	case 2:
		g_WinScreen.Update(elapsedSec);
		break;
	case 3:
		g_LoseScreen.Update(elapsedSec);
		break;
	case 4:
		g_Settings.Update(elapsedSec);
		break;
	}
}

void End()
{
	DeleteGameAssets();
}
#pragma endregion gameFunctions

#pragma region ownDefinitions

#pragma endregion ownDefinitions