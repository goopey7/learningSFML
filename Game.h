//Copyright Sam Collier 2022
#pragma once

#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

#include "World.h"

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

	private:
		sf::RenderWindow* window;
		sf::Event ev;

		World* world;

		// For FixedUpdate
		const int TicksPerSec = 60;
};

