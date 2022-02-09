//Copyright Sam Collier 2022
#pragma once

#include "Actor.h"

class Aircraft : public Actor
{
	public:
		Aircraft();
		~Aircraft();
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Sprite sprite;
		
};

