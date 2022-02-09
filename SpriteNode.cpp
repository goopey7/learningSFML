//Copyright Sam Collier 2022

#include "SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite,states);
}

