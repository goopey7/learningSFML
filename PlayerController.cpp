//Copyright Sam Collier 2022

#include "PlayerController.h"

struct AircraftMover
{
	AircraftMover(float vx, float vy)
		: velocity(vx,vy)
	{
	}

	void operator() (Aircraft& aircraft, const float dt) const
	{
		sf::Vector2f pos = aircraft.getPosition();
		aircraft.setPosition(pos.x + velocity.x*dt, pos.y + velocity.y*dt);
	}

	sf::Vector2f velocity;
};
