//Copyright Sam Collier 2022

#include "Hero.h"

Hero::Hero(const TextureHolder& textures)
	: textures(textures),sprite(textures.get(Textures::Hero))
{
	for(int i=0;i<4;i++)
	{
		frames.emplace_back(i*50,0,50,37);
	}
	sprite.setTextureRect(frames[animIndex]);
}

void Hero::fixedUpateCurrent(const float dt)
{
	timeBetweenFrames+=dt;
	if(timeBetweenFrames >= animSecPerFrame)
	{
		animIndex++;
		if(animIndex==4)
			animIndex=0;
		sprite.setTextureRect(frames[animIndex]);
		timeBetweenFrames = 0.f;
	}
	//accelerateY(9.81f);
	Actor::fixedUpateCurrent(dt);
}

unsigned int Hero::getCategory() const
{
	return Category::PlayerHero;
}

void Hero::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite,states);
}

