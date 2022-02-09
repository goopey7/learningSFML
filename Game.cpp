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
	world = new World(*window);
}

Game::~Game()
{
	delete world;
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

void Game::update(const float dt)
{
	world->update(dt);
}

void Game::fixedUpdate(const float dt)
{
	world->fixedUpdate(dt);
}

void Game::render()
{
	window->clear();
	world->draw();
	//window->setView(window->getDefaultView());
	window->display();
}

void Game::run()
{
	const sf::Time TimePerUpdate = sf::seconds(1.f/TicksPerSec);
	sf::Clock timer;
	sf::Time prevTime = sf::Time::Zero;
	sf::Time timeBetweenTicks = sf::Time::Zero;
	
	// GAME LOOP
	while(window->isOpen())
	{
		// get the time
		sf::Time currentTime = timer.getElapsedTime();
		sf::Time dt = currentTime - prevTime;
		timeBetweenTicks += dt;
		prevTime = currentTime;

		// Realtime Events
		handleEvents();
		update(dt.asSeconds());

		// Fixed Time Events
		while(timeBetweenTicks >= TimePerUpdate)
		{
			fixedUpdate(dt.asSeconds());
			// subtract a fixedUpdate worth of ticks
			timeBetweenTicks-=TimePerUpdate;
		}

		// Rendering
		render();
	}
}

