//Copyright Sam Collier 2022
#pragma once

#include "Aircraft.h"
#include "CommandQueue.h"

class PlayerController
{
	public:
		PlayerController();

		enum Action
		{
			MoveUp,
			MoveLeft,
			MoveDown,
			MoveRight,
			ShowPos
		};

		void bindHeldKey(Action heldAction, sf::Keyboard::Key key, bool remap = true);
		sf::Keyboard::Key getBindedKey(Action action) const;

		void handleEvent(const sf::Event& event, CommandQueue& commands);
		void handleHeldInput(CommandQueue& commands);
	private:
		std::map<sf::Keyboard::Key, bool> wasReleased;
		std::map<sf::Keyboard::Key, Action> keyBindings;
		std::map<Action,Command> pressedActions;
		std::map<Action,Command> heldActions;
		std::map<Action,Command> releasedActions;
};

