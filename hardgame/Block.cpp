#include "Block.h"


Block::Block(float t_X, float t_Y, float t_Edge, bool t_Color)
{
	block.setPosition(t_X, t_Y);
	block.setSize(Vector2f(t_Edge, t_Edge));
	if (t_Color) block.setFillColor(Color(224, 218, 254));
}

void Block::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->block, state);
}