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
	Point2f newScale{t->width * (scale/100.0f), t->height * (scale/100.0f)};
	DrawTexture(*t, Rectf( Pos.x,Pos.y, newScale.x, newScale.y ));
}

#pragma endregion

#pragma region UIElements
Texture g_Font{};
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

	bool UIButton(Point2f Pos, Texture* t, float scale, bool Active) {
		AllData data_{};
		data_.p = &g_UiText;
		data_.Pos = Pos;
		data_.t = t;
		data_.scale = scale;
		if (Input.mousePos.x > Pos.x && Input.mousePos.x < Pos.x + t->width  * (scale / 100.0f) 
		 && Input.mousePos.y > Pos.y && Input.mousePos.y < Pos.y + t->height * (scale / 100.0f)) {
			//data_.c = Color4f(0, 0, 0, 0.3f);
			//data_;
			//data_.p = &g_UiRect;
			//data_.Pos = Pos;
			//data_.Size = Point2f(t->width, t->height);
			//g_UIData.push_back(data_);
			data_.scale = scale += 10;
		}
		g_UIData.push_back(data_);
		return (Input.ClickUp == Input.MB1 && Input.mousePos.x > Pos.x && Input.mousePos.x < Pos.x + t->width && Input.mousePos.y > Pos.y && Input.mousePos.y < Pos.y + t->height);
	}

	void FillText(std::string str, Point2f pos, int scale) {
		float sc{128};
		int spacing{(int)(scale * 0.95f )};
		for (int i = 0; i < str.length(); i++)
		{
			if ((int)str[i] != ' ') {
				int ascii = (int)str[i] - '#';
				if (str[i] == '!')ascii = '{' - '#';
				if (str[i] == '"')ascii = '|' - '#';
				int p{ spacing * i }; // size texture
				DrawTexture(g_Font, Rectf(pos.x + p, pos.y, scale/ 100.0f * sc, scale / 100.0f * sc), 
					Rectf(float((ascii % 15) * sc),	float((1 + ascii / 15) * sc), sc, sc));
			}
		}
	}
}
#pragma endregion