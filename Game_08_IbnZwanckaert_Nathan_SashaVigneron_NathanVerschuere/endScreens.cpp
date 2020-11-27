#include "pch.h"
#include "endScreens.h"
using namespace UI;
using namespace utils;
extern float g_WindowHeight;
extern float g_WindowWidth;
extern InputS Input;
extern INT8 g_Scene;
extern MainGame g_MainGame;

#pragma region WinScreen
void WinScreen::Draw() {
	DrawScreen();
}

void WinScreen::Update(float elapsedSec) {

}

#pragma endregion

#pragma region LoseScreen
void LoseScreen::Draw() {
	DrawScreen();
}

void LoseScreen::Update(float elapsedSec) {
	
}
#pragma endregion

void DrawScreen() {
	const Point2f leftBottom{ 421,175 }, size{779,354};
	DrawTexture(*GetTexture("BackgroundMenu.png"), Point2f(0, 0));

	SetColor(38 / 255.0f, 32 / 255.0f, 60 / 255.0f);
	FillRect(leftBottom,size.x,size.y);

	float scaleButton{ 20 };
	if (UIButton(Point2f(g_WindowWidth/2 - (GetTexture("return.png")->width * (scaleButton / 100.0f) + 50), scaleButton),GetTexture("return.png"),50)) {
		g_Scene = 0;
		g_MainGame.reset();
	}
}