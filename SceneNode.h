//Copyright Sam Collier 2022
#pragma once

#include <vector>
#include <memory>
#include <cassert>

#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		SceneNode() = default;
		typedef std::unique_ptr<SceneNode> Ptr;
		void attachChild(Ptr child);
		Ptr detachChild(const SceneNode& node);

		void fixedUpdate(const float dt);
		void update(const float dt);
		sf::Transform getWorldTransform() const;
		sf::Vector2f getWorldPosition() const;

	private:
		std::vector<Ptr> children;
		SceneNode* parent = nullptr;

		// final means that children of this class cannot override it
		// draw renders the entire node and children
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

		// only draws the current node but not it's children
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{};

		virtual void fixedUpateCurrent(const float dt){};
		void fixedUpdateChildren(const float dt);
		virtual void updateCurrent(const float dt){};
		void updateChildren(const float dt);


};

