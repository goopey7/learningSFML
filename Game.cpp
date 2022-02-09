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

void Game::update(const float dt)
{
}

void Game::fixedUpdate(const float dt)
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
	TextureHolder textures;
	textures.load(Textures::Aircraft,"images/Eagle.png");
	textures.load(Textures::Desert,"images/Desert.png");

	sf::Sprite aircraft;
	aircraft.setTexture(textures.get(Textures::Aircraft));
	sf::Sprite desert;
	textures.get(Textures::Desert).setRepeated(true);
	desert.setTexture(textures.get(Textures::Desert));
	desert.setTextureRect(sf::IntRect(0,0,window->getSize().x,window->getSize().y));

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
		window->clear();
		window->draw(desert);
		window->draw(aircraft);
		window->display();
		//render();
	}
}

