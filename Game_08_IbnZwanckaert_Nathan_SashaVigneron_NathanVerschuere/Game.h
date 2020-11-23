#pragma once
using namespace utils;
using namespace UI;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Name Project - Name, Firstname - 1DAExx" };
InputS Input{};
// Change the window dimensions here
float g_WindowWidth{ 1024 };
float g_WindowHeight{ 768 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here
INT8 g_Scene{};
// Declare your own functions here
void Menu_Scene();
void Main_Game();
#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions