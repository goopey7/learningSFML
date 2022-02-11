//Copyright Sam Collier 2022
#pragma once

#include "SceneNode.h"

class Actor : public SceneNode
{
	public:
		void setVelocity(sf::Vector2f velocity);
		void setVelocity(float vx,float vy);
		void setVelocityX(float vx);
		void setVelocityY(float vy);
		void accelerate(sf::Vector2f acceleration);
		void accelerate(float ax, float ay);
		void accelerateX(float ax);
		void accelerateY(float ay);
		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpateCurrent(const float dt) override;
		sf::Vector2f getVelocity() const;
	private:
			sf::Vector2f velocity;
};

