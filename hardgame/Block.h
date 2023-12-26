#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Block : public Drawable
{
public:
	Block(float t_X, float t_Y,float t_Edge, bool t_Color);
	Block() = delete;
	~Block() = default;

private:
	void draw(RenderTarget& target, RenderStates state) const override;
	RectangleShape block;
};