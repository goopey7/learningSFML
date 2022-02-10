//Copyright Sam Collier 2022

#include "CommandQueue.h"

void CommandQueue::push(const Command& command)
{
	queue.push(command);
}

Command CommandQueue::pop()
{
	Command popped = queue.front();
	queue.pop();
	return popped;
}

bool CommandQueue::isEmpty()
{
	return queue.empty();
}

