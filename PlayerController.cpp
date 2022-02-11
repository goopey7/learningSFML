//Copyright Sam Collier 2022

#include "PlayerController.h"
#include <cmath>

enum StopDir
{
	None,
	Up,
	Left,
	Down,
	Right,
};

struct AircraftMover
{
	AircraftMover(float vx, float vy, StopDir dir = StopDir::None)
		: velocity(vx,vy),dir(dir)
	{
	}

	AircraftMover(StopDir dir)
		: dir(dir)
	{
	}

	void operator() (Aircraft& aircraft, const float dt) const
	{
		switch(dir)
		{
			case StopDir::Up:
			{
				if(aircraft.getVelocity().y < 0)
					aircraft.setVelocityY(0.f);
				break;
			}
			case StopDir::Left:
			{
				if(aircraft.getVelocity().x < 0)
					aircraft.setVelocityX(0.f);
				break;
			}
			case StopDir::Down:
			{
				if(aircraft.getVelocity().y > 0)
					aircraft.setVelocityY(0.f);
				break;
			}
			case StopDir::Right:
			{
				if(aircraft.getVelocity().x > 0)
					aircraft.setVelocityX(0.f);
				break;
			}
			case StopDir::None:
			{
				if(velocity.x != 0)
					aircraft.setVelocityX(velocity.x * dt);
				if(velocity.y != 0)
					aircraft.setVelocityY(velocity.y * dt);

				// keep velocity constant using 45 - 45 - 90 rule
				if(velocity.x != 0 && velocity.y != 0)
				{
					aircraft.setVelocity(velocity/sqrtf(2.f) * dt);
				}
			}
		}
	}

	sf::Vector2f velocity;
	StopDir dir;
};

PlayerController::PlayerController()
{
	keyBindings[sf::Keyboard::W] = MoveUp;
	keyBindings[sf::Keyboard::A] = MoveLeft;
	keyBindings[sf::Keyboard::S] = MoveDown;
	keyBindings[sf::Keyboard::D] = MoveRight;
	keyBindings[sf::Keyboard::P] = ShowPos;

	const float playerSpeed = 3000.f;
	
	// Pressed Actions
	pressedActions[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f,-playerSpeed));
	pressedActions[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed,0.f));
	pressedActions[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f,playerSpeed));
	pressedActions[MoveRight].action = derivedAction<Aircraft>(AircraftMover(playerSpeed,0.f));
	pressedActions[ShowPos].action = [] (SceneNode& s, const float dt)
	{
		std::cout << s.getPosition().x << ',' << s.getPosition().y << '\n';
	};

	// Held Actions

	// Released Actions
	releasedActions[MoveUp].action = derivedAction<Aircraft>(AircraftMover(StopDir::Up));
	releasedActions[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(StopDir::Left));
	releasedActions[MoveDown].action = derivedAction<Aircraft>(AircraftMover(StopDir::Down));
	releasedActions[MoveRight].action = derivedAction<Aircraft>(AircraftMover(StopDir::Right));

	// Init categroies
	for(auto &binding : heldActions)
	{
		binding.second.category = Category::PlayerAircraft;
	}
	for(auto &binding : pressedActions)
	{
		binding.second.category = Category::PlayerAircraft;
	}
	for(auto &binding : releasedActions)
	{
		binding.second.category = Category::PlayerAircraft;
	}
}

void PlayerController::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	for(auto binding : keyBindings)
	{
		if(sf::Keyboard::isKeyPressed(binding.first) && wasReleased[binding.first])
		{
			wasReleased[binding.first] = false;
			commands.push(pressedActions[binding.second]);
		}
		else if(!sf::Keyboard::isKeyPressed(binding.first) && !wasReleased[binding.first])
		{
			wasReleased[binding.first] = true;
			commands.push(releasedActions[binding.second]);
		}
	}
}

void PlayerController::handleHeldInput(CommandQueue& commands)
{
	for(auto binding : keyBindings)
	{
		if(sf::Keyboard::isKeyPressed(binding.first))
		{
			// ensures that only actions in the map
			// are pushed
			if(heldActions.count(binding.second) == 1)
			{
				commands.push(heldActions[binding.second]);
			}
		}
	}
}

void PlayerController::bindHeldKey(Action action, sf::Keyboard::Key key, bool remap)
{
	// When remapping we don't want
	// the previous binding to still be mapped
	// to the action. At least for now
	if(remap)
	{
		for(auto binding : keyBindings)
		{
			if(binding.second == action)
			{
				keyBindings.erase(binding.first);
			}
		}
	}

	keyBindings[key] = action;
}

sf::Keyboard::Key PlayerController::getBindedKey(Action action) const
{
	for(auto binding : keyBindings)
	{
		if(binding.second == action)
			return binding.first;
	}
	return sf::Keyboard::KeyCount;
}


