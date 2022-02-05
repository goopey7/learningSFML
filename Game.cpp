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

void Game::updateDt()
{
	dt = dtClock.restart().asSeconds();

	system("clear");
	std::cout << "dt: " << dt << std::endl;
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
		updateDt();
		handleEvents();
		update();
		render();
	}
}

