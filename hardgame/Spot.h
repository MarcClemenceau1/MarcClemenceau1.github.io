#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Spot : public Drawable
{
public:
	Spot(float t_X, float t_Y, float t_Width, float t_Height);
	Spot() = delete;
	~Spot() = default;

	float top();
	float bottom();
	float right();
	float left();

	Color getColor();

	bool tap();
	//bool illuminate();

private:
	void draw(RenderTarget& target, RenderStates state) const override;
	RectangleShape spot;

	Color color = Color(159, 239, 155);

	bool half = false;
};