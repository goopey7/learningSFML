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

class State
{
	public:
		State();
		~State();

		virtual void update() = 0;
		virtual void render() = 0;

	protected:

	private:
		
};

