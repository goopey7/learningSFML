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
		void update(const float dt);
		void fixedUpdate(const float dt);
		void render();
		void run();

	protected:

	private:
		sf::RenderWindow* window;
		sf::Event ev;

		// For FixedUpdate
		const int TicksPerSec = 60;
};

