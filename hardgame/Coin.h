#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Coin : public Drawable
{
public:

	Coin(float t_X, float t_Y);
	Coin() = delete;
	~Coin() = default;

	void update();
	void setCollected(bool x);

	float top();
	float bottom();
	float right();
	float left();

	bool isCollected();

private:

	void draw(RenderTarget& target, RenderStates state) const override;
	CircleShape in_circle, ex_circle;

	const float in_circleRadius{ 5.f };
	const float ex_circleRadius{ 10.f };

	bool collected = false;
};

