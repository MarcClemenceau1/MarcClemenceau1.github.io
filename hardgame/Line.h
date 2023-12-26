#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Line : public Drawable
{
public:
	Line(float t_X, float t_Y, float t_Width, float t_Height);
	Line() = delete;
	~Line() = default;

	float top();
	float bottom();
	float right();
	float left();

private:
	void draw(RenderTarget & target, RenderStates state) const override;
	RectangleShape line;
};

