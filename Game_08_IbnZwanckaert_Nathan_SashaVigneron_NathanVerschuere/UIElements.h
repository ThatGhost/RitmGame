#pragma once
#include "utils.h"
//struct Texture;
using utils::Texture;

class UIElements
{
public:
	virtual void Draw() = 0;
	Color4f c;
	Point2f Pos, Pos2, Pos3, Size;
	Rectf r;
	Texture* t;
	float scale{100};
	bool isActive{};
};


class UIRect :public UIElements {
public :
	virtual void Draw() override;
	UIRect();
	//UIRect(Point2f pPos, Point2f pSize);
};

class UIElip :public UIElements {
public:
	virtual void Draw() override;
	UIElip();
};

class UITria :public UIElements {
public:
	virtual void Draw() override;
	UITria();
};

class UItext :public UIElements {
public:
	virtual void Draw() override;
	UItext();
};

struct AllData {
	UIElements* p;
	Point2f Pos{};
	Point2f Pos2{};
	Point2f Pos3{};
	Point2f Size{};
	int scale{};
	Color4f c{0,0,0,1};
	Texture* t{};
	Rectf r{};
};

namespace UI {
	void UIRectangle(Point2f Pos, Point2f Size, Color4f c);
	bool UIButton(Point2f Pos, Point2f Size, Color4f c, bool Active = true);
	void UITexture(Point2f Pos, Texture* t, const float scale);
	bool UIButton(Point2f Pos, Texture* t, float scale, bool Active = true);
	void UIElipse(Point2f Pos, Point2f Size, Color4f c);
	void UITriangle(Point2f Pos1, Point2f Pos2, Point2f Pos3, Color4f c);
	void FillText(std::string str, Point2f pos, int scale, bool red = false);
}
