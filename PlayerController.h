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
		};

		void bindKey(Action action, sf::Keyboard::Key key);
		sf::Keyboard::Key getBindedKey(Action action) const;

		void handleEvent(const sf::Event& event, CommandQueue& commands);
		void handleRealtimeInput(CommandQueue& commands);
	private:
		static bool isRealtimeAction(Action action);

		std::map<sf::Keyboard::Key, Action> keyBindings;
		std::map<Action,Command> actionBindings;

};

