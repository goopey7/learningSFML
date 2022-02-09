//Copyright Sam Collier 2022
#pragma once

#include "SceneNode.h"

class SpriteNode : public SceneNode
{
	public:
		// explicit means that this constructor cannot be used implicitly
		// ie. cannot take a texture and infer to use this constructor and make a SpriteNode
		// for clearer example read this: 
		//https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
		// also restricts me initializing variables outside the definition with the :
		explicit SpriteNode(const sf::Texture& texture);
		SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

	private:
		sf::Sprite sprite;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
};

