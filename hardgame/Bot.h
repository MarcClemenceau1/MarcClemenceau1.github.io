#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bot : public Drawable
{
public:
	Bot(float t_X, float t_Y, char t_Turn, float t_Distance);
	Bot() = delete;
	~Bot() = default;

	void update();
	void setFrozen(bool x);

	float top();
	float bottom();
	float right();
	float left();

	float deviation();

private:
	void draw(RenderTarget& target, RenderStates state) const override;
	CircleShape in_circle, ex_circle;

	const float in_circleRadius{ 8.f };
	const float ex_circleRadius{ 13.f };

	const float circleVelocity{ 1.5f };
	Vector2f velocity{ 0.f, 0.f };
	Vector2f start_point{ 0.f, 0.f };

	bool frozen = false;
	float distance;
};