//Copyright Sam Collier 2022

#include "Actor.h"
#include <iostream>

void Actor::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Actor::setVelocity(float vx,float vy)
{
	velocity = sf::Vector2f(vx,vy);
}

void Actor::accelerate(sf::Vector2f acceleration)
{
	velocity += acceleration;
}

void Actor::accelerate(float ax, float ay)
{
	velocity += sf::Vector2f(ax,ay);
}

sf::Vector2f Actor::getVelocity() const
{
	return velocity;
}

void Actor::updateCurrent(const float dt)
{
}

void Actor::fixedUpateCurrent(const float dt)
{
	move(velocity*dt);
}

