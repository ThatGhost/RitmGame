#include "pch.h"
#include "UIElements.h"

using namespace utils;
extern std::vector<AllData> g_UIData;

extern UIRect g_UiRect;
extern UIElip g_UiElip;
extern UITria g_UiTria;
extern UItext g_UiText;
extern InputS Input;

#pragma region classes
//-----------------------------------------
//		UIRect
//-----------------------------------------
UIRect::UIRect() {}

void UIRect::Draw() {
	SetColor(c);
	FillRect(Pos.x,Pos.y,Size.x,Size.y);
}

//-----------------------------------------
//		UIElipse
//-----------------------------------------

UIElip::UIElip() {}

void UIElip::Draw() {
	SetColor(c);
	FillEllipse(Pos.x, Pos.y, Size.x, Size.y);
}

//-----------------------------------------
//		UITriangle
//-----------------------------------------

UITria::UITria() {}

void UITria::Draw() {
	SetColor(c);
	FillTriangle(Pos,Pos2,Pos3);
}

//-----------------------------------------
//		UITexture
//-----------------------------------------

UItext::UItext() {}

void UItext::Draw() {
	DrawTexture(*t,Pos,r);
}

#pragma endregion

#pragma region UIElements
namespace UI {
	void UIRectangle(Point2f Pos, Point2f Size, Color4f c) {
		AllData data_{};
		data_.c = c;
		data_.p = &g_UiRect;
		data_.Pos = Pos;
		data_.Size = Size;
		g_UIData.push_back(data_);
	}

	void UIElipse(Point2f Pos, Point2f Size, Color4f c) {
		AllData data_{};
		data_.c = c;
		data_.p = &g_UiElip;
		data_.Pos = Pos;
		data_.Size = Size;
		g_UIData.push_back(data_);
	}

	void UITriangle(Point2f Pos1, Point2f Pos2, Point2f Pos3, Color4f c) {
		AllData data_{};
		data_.c = c;
		data_.Pos = Pos1;
		data_.Pos2 = Pos2;
		data_.Pos3 = Pos3;
		data_.p = &g_UiTria;
		g_UIData.push_back(data_);
	}

	void UITexture(Point2f Pos, Texture* t, const Rectf r) {
		AllData data_{};
		data_.p = &g_UiText;
		data_.t = t;
		data_.r = r;
		data_.Pos = Pos;
		g_UIData.push_back(data_);
	}

	bool UIButton(Point2f Pos, Point2f Size, Color4f c, bool Active) {
		AllData data_{};
		data_.c = c;
		data_.p = &g_UiRect;
		data_.Pos = Pos;
		data_.Size = Size;
		g_UIData.push_back(data_);
		if (Active || (Input.ClickDown == Input.MB1 && Input.mousePos.x > Pos.x && Input.mousePos.x < Pos.x + Size.x && Input.mousePos.y > Pos.y && Input.mousePos.y < Pos.y + Size.y)) {
			data_.c = Color4f(0,0,0,0.3f);
			g_UIData.push_back(data_);
		}
		return (Input.ClickUp == Input.MB1 && Input.mousePos.x > Pos.x && Input.mousePos.x < Pos.x + Size.x && Input.mousePos.y > Pos.y && Input.mousePos.y < Pos.y + Size.y);
	}

	bool UIButton(Point2f Pos, Texture* t, bool Active) {
		AllData data_{};
		data_.p = &g_UiText;
		data_.Pos = Pos;
		data_.t = t;
		g_UIData.push_back(data_);
		if (!Active || (Input.ClickDown == Input.MB1 && Input.mousePos.x > Pos.x && Input.mousePos.x < Pos.x + t->width && Input.mousePos.y > Pos.y && Input.mousePos.y < Pos.y + t->height)) {
			data_.c = Color4f(0, 0, 0, 0.3f);
			data_;
			data_.p = &g_UiRect;
			data_.Pos = Pos;
			data_.Size = Point2f(t->width, t->height);
			g_UIData.push_back(data_);
		}
		return (Input.ClickUp == Input.MB1 && Input.mousePos.x > Pos.x && Input.mousePos.x < Pos.x + t->width && Input.mousePos.y > Pos.y && Input.mousePos.y < Pos.y + t->height);
	}
}
#pragma endregion