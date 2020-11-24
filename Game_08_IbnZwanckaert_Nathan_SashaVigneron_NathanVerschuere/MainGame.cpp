#include "pch.h"
#include "MainGame.h"
using namespace utils;
using namespace UI;

void MainGame::Draw() {
	//draw voor game vieuw/scene
	DrawTexture(*GetTexture("Background.png"),Point2f(0,0));
}

void MainMenu::Draw() {

}