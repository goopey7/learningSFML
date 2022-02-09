//Copyright Sam Collier 2022

#include "SceneNode.h"

void SceneNode::attachChild(Ptr child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	int childFound = -1;
	for(int i=0;i<children.size();i++)
	{
		if(children[i].get() == &node)
		{
			childFound = i;
			break;
		}
	}

	assert(childFound >= 0);

	Ptr returnNode = std::move(children[childFound]);
	returnNode->parent = nullptr;
	children.erase(children.begin() + childFound);
	return returnNode;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Two transforms are applied one after the other using the * operator

	// This takes the parent's absolute transform and then applies the current node's
	// relative transform. So this achieves the absolute world transform of the current node
	// this is also how sf::Sprite handles it by combining it's own transform with the passed
	// render state
	states.transform *= getTransform();

	// now that we have the absolute transform we can draw the node
	drawCurrent(target,states);

	// recursively draw all children
	for(const Ptr& child : children)
	{
		child->draw(target,states);
	}
}


void SceneNode::updateChildren(const float dt)
{
	for(Ptr &child : children)
		child->update(dt);
}

void SceneNode::update(const float dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	// Get absolute transform by accumulating all the transformations up the tree
	// until we reach the root node. That will yield world transform
	for(const SceneNode* node = this; node != nullptr; node = node->parent)
	{
		transform = node->getTransform() * transform;
	}
	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	// Apply transformation of world pos with origin
	return getWorldTransform() * sf::Vector2f();
}

