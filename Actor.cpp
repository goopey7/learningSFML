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
	if(acceleration.x == 0.f)
		velocity.x = 0;
	else if(acceleration.x == -velocity.x)
		velocity.x *= -1;
	// accelerate normally if velocity is zero
	else if(velocity.x == 0 && acceleration.x != 0)
		velocity.x = acceleration.x;
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
	//system("clear");
	//std::cout << "Velocity: " << velocity.x << ',' << velocity.y << '\n';
}

void Actor::fixedUpateCurrent(const float dt)
{
	move(velocity*dt);
}

void Actor::setVelocityX(float vx)
{
	velocity.x = vx;
}

void Actor::setVelocityY(float vy)
{
	velocity.y = vy;
}

void Actor::accelerateX(float ax)
{
	velocity.x += ax;
}

void Actor::accelerateY(float ay)
{
	velocity.y += ay;
}

