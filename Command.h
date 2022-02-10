//Copyright Sam Collier 2022
#pragma once

#include <functional>
#include "SceneNode.h"

struct Command
{
	Command();
	std::function<void(SceneNode&,sf::Time)> action; // The command
	unsigned int category; // The category the command is for
};

