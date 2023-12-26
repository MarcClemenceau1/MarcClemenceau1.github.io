#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Square : public Drawable
{
public:
	Square(float t_X, float t_Y);
	Square() = delete;
	~Square() = default;

	void update();

	void setPossition(Vector2f vector);

	void stepUp(bool x);
	void stepDown(bool x);
	void stepRight(bool x);
	void stepLeft(bool x);

	float top();
	float bottom();
	float right();
	float left();

	void setFrozen(bool x);
	bool getFrozen();

	float getVelocity();

	bool comeBack();
	

private:
	void draw(RenderTarget& target, RenderStates state) const override;
	RectangleShape in_square,ex_square;

	const float in_squareEdge{26.f};
	const float ex_squareEdge{36.f};

	const float squareVelocity{1.f };
	Vector2f velocity{ 0.f, 0.f };

	Vector2f start_point{ 0.f, 0.f };

	bool frozen = false;
	bool half = false;
};
  
