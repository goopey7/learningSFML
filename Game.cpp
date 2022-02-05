//Copyright Sam Collier 2022

#include "Game.h"

void Game::initWindow()
{
	std::ifstream ifs("config/window.cfg");
	std::string title;
	sf::VideoMode windowSize(800,600);
	bool vSyncEnabled = false;
	if(ifs.is_open())
	{
		std::getline(ifs,title);
		ifs >> windowSize.width >> windowSize.height;
		ifs >> vSyncEnabled;
	}
	ifs.close();
	window = new sf::RenderWindow(windowSize,title);
	window->setVerticalSyncEnabled(vSyncEnabled);
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

