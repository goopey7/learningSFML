//Copyright Sam Collier 2022

#include "World.h"


World::World(sf::RenderWindow& window)
	: window(window),
	worldView(window.getDefaultView()),
	worldBounds(0.f,0.f,2000.f,2000.f),
	spawnPos(0.f,0.f)
{
	tmx::Map map;
	map.load("assets/tilemaps/level1.tmx");
	tileLayers.push_back(new MapLayer(map,0));
	loadTextures();
	buildScene();
	worldView.setCenter(spawnPos);
	worldView.zoom(0.5f);
}

void World::loadTextures()
{
	textures.load(Textures::Aircraft,"assets/images/Eagle.png");
	textures.load(Textures::Hero, "assets/playerSprite/adventurer-v1.5-Sheet.png");
}

void World::buildScene()
{
	// Initialize Layers
	for(int i=0;i<LayerCount;i++)
	{
		SceneNode::Ptr layer(new SceneNode());
		sceneLayers[i] = layer.get();
		sceneGraph.attachChild(std::move(layer));
	}
	
	// Aircraft
	std::unique_ptr<Aircraft> leader(new Aircraft(textures));
	leader->setPosition(spawnPos);
	sceneLayers[Foreground]->attachChild(std::move(leader));

	// Hero
	std::unique_ptr<Hero> hero(new Hero(textures));
	hero->setPosition(spawnPos);
	sceneLayers[Foreground]->attachChild(std::move(hero));
}

void World::fixedUpdate(const float dt)
{

	// Broadcast commands to sceneGraph
	while(!commandQueue.isEmpty())
		sceneGraph.onCommand(commandQueue.pop(),dt);

	sceneGraph.fixedUpdate(dt);
}

void World::update(const float dt)
{
	// Update Scene Graph
	sceneGraph.update(dt);
}

void World::draw()
{
	window.setView(worldView);
	window.draw(*tileLayers[0]);
	window.draw(sceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return commandQueue;
}

World::~World()
{
	for(MapLayer* layer : tileLayers)
		delete layer;
	tileLayers.clear();
}

