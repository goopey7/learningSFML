//Copyright Sam Collier 2022
#pragma once

#include "ResourceHolder.h"
#include "Actor.h"

class Hero : public Actor
{
	public:
		Hero(const TextureHolder& textures);
		void fixedUpateCurrent(const float dt) override;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual unsigned int getCategory() const override;

	private:
		sf::Sprite sprite;
		const TextureHolder& textures;
		std::vector<sf::IntRect> frames;
		int animIndex = 0;
		const float animFPS = 5.f;
		const float animSecPerFrame = 1.f / animFPS;
		float timeBetweenFrames = 0.f;
};

