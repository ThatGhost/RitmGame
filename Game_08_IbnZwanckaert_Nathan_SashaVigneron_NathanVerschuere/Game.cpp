#include "pch.h"
#include "Game.h" 
//<<<<<<< Updated upstream
//=======
#include "SoundStream.h"
#include "SoundEffect.h"

//>>>>>>> Stashed changes
//Basic game functions
#pragma region gameFunctions											
void Start()
{
	InitializeGameAssets();
	PlayMusic("bruh.mp3");
	g_MainGame.Start();
	g_MainMenu.Start();
}

void Draw()
{
	SoundStream music{ "Assets/Audio/bruh.mp3" };
	music.Play(1);
	if (music.IsPlaying()) {
		std::cout << "is playing bruh\n";
	}

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
	g_MainGame.Update(elapsedSec);
	g_MainMenu.Update(elapsedSec);
}

void End()
{
	g_MainGame.End();
	g_MainMenu.End();
	DeleteGameAssets();
}
#pragma endregion gameFunctions

#pragma region ownDefinitions

#pragma endregion ownDefinitions