//Copyright Sam Collier 2022

#include "PlayerController.h"

struct AircraftMover
{
	AircraftMover(float vx, float vy, bool stopX=false, bool stopY=false)
		: velocity(vx,vy),bStopX(stopX),bStopY(stopY)
	{
	}

	void operator() (Aircraft& aircraft, const float dt) const
	{
		if(bStopX)
		{
			aircraft.setVelocityX(0.f);
			return;
		}
		aircraft.setVelocity(velocity * dt);
	}

	sf::Vector2f velocity;
	bool bStopX,bStopY;
};

PlayerController::PlayerController()
{
	keyBindings[sf::Keyboard::W] = MoveUp;
	keyBindings[sf::Keyboard::A] = MoveLeft;
	keyBindings[sf::Keyboard::S] = MoveDown;
	keyBindings[sf::Keyboard::D] = MoveRight;
	keyBindings[sf::Keyboard::P] = ShowPos;

	const float playerSpeed = 1500.f;
	//heldActions[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f,-playerSpeed));
	heldActions[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed,0.f));
	//heldActions[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f,playerSpeed));
	heldActions[MoveRight].action = derivedAction<Aircraft>(AircraftMover(playerSpeed,0.f));

	//releasedActions[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f,-playerSpeed));
	releasedActions[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(0.f,0.f,true));
	//releasedActions[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f,playerSpeed));
	releasedActions[MoveRight].action = derivedAction<Aircraft>(AircraftMover(0.f,0.f,true));

	pressedActions[ShowPos].action = [] (SceneNode& s, const float dt)
	{
		std::cout << s.getPosition().x << ',' << s.getPosition().y << '\n';
	};

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
	for(auto pair : wasReleased)
	{
		wasReleased[pair.first] = true;
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


