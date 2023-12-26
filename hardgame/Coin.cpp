#include "Coin.h"


Coin::Coin(float t_X, float t_Y)
{
	in_circle.setPosition(t_X, t_Y);
	in_circle.setRadius(this->in_circleRadius);
	in_circle.setFillColor(Color(254, 200, 3));
	in_circle.setOrigin(this->in_circleRadius, this->in_circleRadius);

	ex_circle.setPosition(t_X, t_Y);
	ex_circle.setRadius(this->ex_circleRadius);
	ex_circle.setFillColor(Color(145, 114, 2));
	ex_circle.setOrigin(this->ex_circleRadius, this->ex_circleRadius);
}

void Coin::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->ex_circle, state);
	target.draw(this->in_circle, state);
}

void Coin::update()
{
	
}
void Coin::setCollected(bool x)
{
	Color in = in_circle.getFillColor();
	Color ex = ex_circle.getFillColor();

	if (x) {
		in.a = 0;
		ex.a = 0;

		collected = true;
	}
	else 
	{
		in.a = 255;
		ex.a = 255;

		collected = false;
	}
	in_circle.setFillColor(in);
	ex_circle.setFillColor(ex);
}

float Coin::top()
{
	return this->ex_circle.getPosition().y - in_circleRadius;
}
float Coin::bottom()
{
	return this->ex_circle.getPosition().y + in_circleRadius;
}
float Coin::right()
{
	return this->ex_circle.getPosition().x + in_circleRadius;
}
float Coin::left()
{
	return this->ex_circle.getPosition().x - in_circleRadius;
}

bool Coin::isCollected() 
{
	return collected;;
}