#include "Line.h"

Line::Line(float t_X, float t_Y, float t_Width, float t_Height)
{
	line.setPosition(t_X, t_Y);
	line.setSize(Vector2f(t_Width, t_Height));
	line.setFillColor(Color(0, 0, 0));

}

void Line::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->line, state);
}

float Line::top()
{
	return this->line.getPosition().y;
}
float Line::bottom()
{
	return this->line.getPosition().y + line.getSize().y;
}
float Line::right()
{
	return this->line.getPosition().x + line.getSize().x;
}
float Line::left()
{
	return this->line.getPosition().x;
}