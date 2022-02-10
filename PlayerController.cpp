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
		aircraft.move(velocity * dt);
	}

	sf::Vector2f velocity;
};

PlayerController::PlayerController()
{
	keyBindings[sf::Keyboard::W] = MoveUp;
	keyBindings[sf::Keyboard::A] = MoveLeft;
	keyBindings[sf::Keyboard::S] = MoveDown;
	keyBindings[sf::Keyboard::D] = MoveRight;

	const float playerSpeed = 15.f;
	actionBindings[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f,-playerSpeed));
	actionBindings[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed,0.f));
	actionBindings[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f,playerSpeed));
	actionBindings[MoveRight].action = derivedAction<Aircraft>(AircraftMover(playerSpeed,0.f));

	for(auto &binding : actionBindings)
	{
		binding.second.category = Category::PlayerAircraft;
	}
}

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
	for(auto binding : keyBindings)
	{
		if(sf::Keyboard::isKeyPressed(binding.first) && isRealtimeAction(binding.second))
		{
			commands.push(actionBindings[binding.second]);
		}
	}
}

bool PlayerController::isRealtimeAction(Action action)
{
	switch(action)
	{
		case MoveUp:
		case MoveLeft:
		case MoveDown:
		case MoveRight:
			return true;
		default:
			return false;
	}
}

void PlayerController::bindKey(Action action, sf::Keyboard::Key key)
{
	// When remapping we don't want
	// the previous binding to still be mapped
	// to the action. At least for now
	for(auto binding : keyBindings)
	{
		if(binding.second == action)
		{
			keyBindings.erase(binding.first);
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


