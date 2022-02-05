//Copyright Sam Collier 2022

#include "Game.h"

void Game::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(800,600), "Learning SFML");
}

Game::Game()
{
	initWindow();
}

Game::~Game()
{
	delete window;
}

void Game::handleEvents()
{
	while(window->pollEvent(ev))
	{
		if(ev.type == sf::Event::Closed)
			window->close();
	}
}

void Game::update()
{
}

void Game::render()
{
	window->clear();

	// render stuff

	window->display();
}

void Game::run()
{
	while(window->isOpen())
	{
		handleEvents();
		update();
		render();
	}
}

