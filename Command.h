//Copyright Sam Collier 2022
#pragma once

#include <functional>
#include "SceneNode.h"

class SceneNode;
struct Command
{
	Command();
	std::function<void(SceneNode&,const float dt)> action; // The command
	unsigned int category; // The category the command is for
};

