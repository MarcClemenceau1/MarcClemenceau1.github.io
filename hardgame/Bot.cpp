#include "Bot.h"


Bot::Bot(float t_X, float t_Y, char t_Turn, float t_Distance)
{
	in_circle.setPosition(t_X, t_Y);
	in_circle.setRadius(this->in_circleRadius);
	in_circle.setFillColor(Color(0, 0, 255));
	in_circle.setOrigin(this->in_circleRadius, this->in_circleRadius);

	ex_circle.setPosition(t_X, t_Y);
	ex_circle.setRadius(this->ex_circleRadius);
	ex_circle.setFillColor(Color(0, 0, 68));
	ex_circle.setOrigin(this->ex_circleRadius, this->ex_circleRadius);

	this->start_point = { t_X,t_Y };
	this->distance = t_Distance;

	if (t_Turn == 'U') velocity.y = -circleVelocity;
	if (t_Turn == 'D') velocity.y = circleVelocity;
	if (t_Turn == 'L') velocity.x = -circleVelocity;
	if (t_Turn == 'P') velocity.x = circleVelocity;
}

void Bot::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->ex_circle, state);
	target.draw(this->in_circle, state);
}

void Bot::update()
{
	if (frozen) return;
	ex_circle.move(this->velocity);
	in_circle.move(this->velocity);

	if (deviation() >= distance) velocity = -velocity;
}
void Bot::setFrozen(bool x) 
{
	frozen = x;
}

float Bot::top()
{
	return this->ex_circle.getPosition().y - in_circleRadius ;
}
float Bot::bottom()
{
	return this->ex_circle.getPosition().y + in_circleRadius;
}
float Bot::right()
{
	return this->ex_circle.getPosition().x + in_circleRadius;
}
float Bot::left()
{
	return this->ex_circle.getPosition().x - in_circleRadius;
}

float Bot::deviation()
{
	float distX = abs(start_point.x - this->in_circle.getPosition().x);
	float distY = abs(start_point.y - this->in_circle.getPosition().y);

	return distX + distY + this->ex_circleRadius;
}

