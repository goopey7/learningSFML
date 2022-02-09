//Copyright Sam Collier 2022
#pragma once

#include <vector>
#include <memory>
#include <cassert>

#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		SceneNode();
		typedef std::unique_ptr<SceneNode> Ptr;
		void attachChild(Ptr child);
		Ptr detachChild(const SceneNode& node);

	private:
		std::vector<Ptr> children;
		SceneNode* parent;

		// final means that children of this class cannot override it
		// draw renders the entire node and children
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

		// only draws the current node but not it's children
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

