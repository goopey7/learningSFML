//Copyright Sam Collier 2022

#include "Aircraft.h"

Aircraft::Aircraft()
{
}

Aircraft::~Aircraft()
{
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite,states);
}

