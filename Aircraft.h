//Copyright Sam Collier 2022
#pragma once

#include "ResourceHolder.h"
#include "Actor.h"

class Aircraft : public Actor
{
	public:
		Aircraft(const TextureHolder& textures);
		~Aircraft();
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpateCurrent(const float dt) override;
		virtual unsigned int getCategory() const override;

	private:
		sf::Sprite sprite;
		const TextureHolder& textures;
		
};

