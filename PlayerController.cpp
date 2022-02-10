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

void PlayerController::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::P)
		{
			Command outputPos;
			outputPos.category = Category::PlayerAircraft;
			outputPos.action = [] (SceneNode& s, const float dt)
			{
				std::cout << s.getPosition().x << ',' << s.getPosition().y << '\n';
			};
			commands.push(outputPos);
		}
	}
}

void PlayerController::handleRealtimeInput(CommandQueue& commands)
{
	const float playerSpeed = 30.f;


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Command moveUp;
		moveUp.category = Category::PlayerAircraft;
		moveUp.action = derivedAction<Aircraft>(AircraftMover(0.f,-playerSpeed));
		commands.push(moveUp);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(-playerSpeed,0.f));
		commands.push(moveLeft);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Command moveDown;
		moveDown.category = Category::PlayerAircraft;
		moveDown.action = derivedAction<Aircraft>(AircraftMover(0.f,playerSpeed));
		commands.push(moveDown);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Command moveRight;
		moveRight.category = Category::PlayerAircraft;
		moveRight.action = derivedAction<Aircraft>(AircraftMover(playerSpeed,0.f));
		commands.push(moveRight);
	}
}

