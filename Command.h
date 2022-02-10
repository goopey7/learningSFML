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

// This function takes in a function on a child of SceneNode and converts it to a function
// on the SceneNode base class
template <typename GameObject, typename Function>
std::function<void(SceneNode&, const float)> derivedAction(Function fn)
{
	// This lambda expression uses a capture list '[=]'
	// means that variables referenced from the body such as fn
	// are captured by value
	return [=] (SceneNode& node, const float dt)
	{
		fn(static_cast<GameObject&>(node),dt);
	};
}
// derivedAction acts as an adapter for when we build commands
// it makes the implementation of command actions look cleaner
// since it deals with the casting for us
