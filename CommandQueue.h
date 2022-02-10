//Copyright Sam Collier 2022
#pragma once

#include <queue>
#include "Command.h"

// Basic wrapper for std::queue for distributing commands
class CommandQueue
{
	public:
		void push(const Command& command);
		Command pop();
		bool isEmpty();

	private:
		std::queue<Command> queue;
};

