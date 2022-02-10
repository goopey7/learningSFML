//Copyright Sam Collier 2022
#pragma once

#include "Aircraft.h"
#include "CommandQueue.h"

class PlayerController
{
	public:
		void handleEvent(const sf::Event& event, CommandQueue& commands);
		void handleRealtimeInput(CommandQueue& commands);
};

