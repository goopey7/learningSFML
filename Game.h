//Copyright Sam Collier 2022
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

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

