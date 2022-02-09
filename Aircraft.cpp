//Copyright Sam Collier 2022

#include "Aircraft.h"

Aircraft::Aircraft(const TextureHolder& textures)
	: textures(textures), sprite(textures.get(Textures::Aircraft))
{
	// Center the origin
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

Aircraft::~Aircraft()
{
}

// Super easy to to render Actors since we don't have to worry about transforms
// which are handled by SceneNode
void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite,states);
}

void Aircraft::updateCurrent(const float dt)
{
	sf::Vector2f pos = getWorldPosition();
	std::cout << "Player Pos " << pos.x << "," << pos.y << "\n";
}

