//Copyright Sam Collier 2022
#pragma once

#include <vector>
#include <memory>
#include <cassert>

class SceneNode
{
	public:
		SceneNode();
		typedef std::unique_ptr<SceneNode> Ptr;
		void attachChild(Ptr child);
		Ptr detachChild(const SceneNode& node);

	private:
		std::vector<Ptr> children;
		SceneNode* parent;
};

