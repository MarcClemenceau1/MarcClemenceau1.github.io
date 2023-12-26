#include "Spot.h"


Spot::Spot(float t_X, float t_Y, float t_Width, float t_Height)
{
	spot.setPosition(t_X, t_Y);
	spot.setSize(Vector2f(t_Width, t_Height));
	spot.setFillColor(color);
}

void Spot::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->spot, state);
}

float Spot::top()
{
	return this->spot.getPosition().y;
}
float Spot::bottom()
{
	return this->spot.getPosition().y + spot.getSize().y;
}
float Spot::right()
{
	return this->spot.getPosition().x + spot.getSize().x;
}
float Spot::left()
{
	return this->spot.getPosition().x;
}

Color Spot::getColor()
{
	return this->spot.getFillColor();
}


bool Spot::tap()
{
	if (half == true && color.r == 159) return true;
	if (!half) {
		if (color.r == 70) {
			half = true;
		}else {
			color.r--, color.g--, color.b--;
		}
	}else {
		color.r++, color.g++, color.b++;
	}
	this->spot.setFillColor(color);
	return false;
}