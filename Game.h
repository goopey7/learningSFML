//Copyright Sam Collier 2022
#pragma once

#include "State.h"

class Game
{
	public:
		Game();
		~Game();
		void initWindow();

		void handleEvents();
		void updateDt();
		void update();
		void render();
		void run();

	protected:

	private:
		sf::RenderWindow* window;
		sf::Event ev;

		sf::Clock dtClock;
		float dt;
};

