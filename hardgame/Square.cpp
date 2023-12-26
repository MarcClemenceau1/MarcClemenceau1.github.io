#include "Square.h"


Square::Square(float t_X, float t_Y)
{
	in_square.setPosition(t_X, t_Y);
	in_square.setSize(Vector2f(this->in_squareEdge, this->in_squareEdge));
	in_square.setFillColor(Color(255, 0, 0));
	in_square.setOrigin(this->in_squareEdge/2, this->in_squareEdge/2);

	ex_square.setPosition(t_X, t_Y);
	ex_square.setSize(Vector2f(this->ex_squareEdge, this->ex_squareEdge));
	ex_square.setFillColor(Color(127, 0, 0));
	ex_square.setOrigin(this->ex_squareEdge/2, this->ex_squareEdge/2);

	this->start_point = { t_X,t_Y };
}

void Square::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->ex_square, state);
	target.draw(this->in_square, state);
}

void Square::update()
{
	if (frozen) {
		comeBack();
	}
}

void Square::setPossition(Vector2f vector)
{
	in_square.setPosition(vector);
	ex_square.setPosition(vector);
	start_point = vector;
}


void Square::stepUp(bool x)
{
	
	
	if ((Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))&& !frozen && x)
	{
		velocity.y = -squareVelocity;
	}
	if (!x) velocity.y = squareVelocity;

	ex_square.move(this->velocity);
	in_square.move(this->velocity);
	
	velocity.y = 0.f;
}
void Square::stepDown(bool x)
{


	if ((Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))&& !frozen && x)
	{
		velocity.y = squareVelocity;
	}
	if (!x) velocity.y = -squareVelocity;

	ex_square.move(this->velocity);
	in_square.move(this->velocity);

	velocity.y = 0.f;
}
void Square::stepRight(bool x)
{


	if ((Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))&& !frozen && x)
	{
		velocity.x = squareVelocity;
	}
	if (!x) velocity.x = -squareVelocity;

	ex_square.move(this->velocity);
	in_square.move(this->velocity);

	velocity.x = 0.f;
}
void Square::stepLeft(bool x)
{


	if ((Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))&& !frozen && x)
	{
		velocity.x = -squareVelocity;
	}
	if (!x) velocity.x = squareVelocity;

	ex_square.move(this->velocity);
	in_square.move(this->velocity);

	velocity.x = 0.f;
}

float Square::getVelocity()
{
	return squareVelocity;
}

float Square::top()
{
	return this->ex_square.getPosition().y - ex_squareEdge/2;
}
float Square::bottom()
{
	return this->ex_square.getPosition().y + ex_squareEdge/2;
}
float Square::right()
{
	return this->ex_square.getPosition().x + ex_squareEdge/2;
}
float Square::left()
{
	return this->ex_square.getPosition().x - ex_squareEdge/2;
}


void Square::setFrozen(bool x)
{
	frozen = x;
}
bool Square::getFrozen() {
	return frozen;
}


bool Square::comeBack()
{
	Color inColor = in_square.getFillColor();
	Color exColor = ex_square.getFillColor();

	if (half && inColor.a == 255) {
		half = false;
		frozen = false;
		return true;
	}

	if (inColor.a == 0) {
		half = true;
		in_square.setPosition(start_point);
		ex_square.setPosition(start_point);
	}
	if (!half) {
		inColor.a--, exColor.a--;
	}else inColor.a++, exColor.a++;

	in_square.setFillColor(inColor);
	ex_square.setFillColor(exColor);

	return false;
}
