#include "pch.h"
#include "MainGame.h"
extern float g_WindowHeight;
extern float g_WindowWidth;
using namespace utils;
using namespace UI;

#pragma region Game
void MainGame::Start() {
	
}

void MainGame::Draw() {
	DrawTexture(*GetTexture("Background.png"),Point2f(0,0));
}

void MainGame::End() {

}

void MainGame::Update(float elapsedSec) {

}
#pragma endregion Menu

#pragma region Menu
void MainMenu::Start() {

}

void MainMenu::Draw() {
	DrawTexture(*GetTexture("Background.png"), Point2f(0, 0));

}

void MainMenu::End() {

}

void MainMenu::Update(float elapsedSec) {

}
#pragma endregion Menu