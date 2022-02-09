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

