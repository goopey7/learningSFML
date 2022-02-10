//Copyright Sam Collier 2022

#include "World.h"


World::World(sf::RenderWindow& window)
	: window(window),
	worldView(window.getDefaultView()),
	worldBounds(0.f,0.f,2000.f,2000.f),
	spawnPos(3200.f,3200.f)
{
	map.load("assets/untitled.tmx");
	for(int i=0;i<map.getLayers().size();i++)
	{
		layers.push_back(new MapLayer(map,i));
	}
	loadTextures();
	buildScene();
	worldView.setCenter(spawnPos);
	worldView.zoom(0.5f);
}

void World::loadTextures()
{
	textures.load(Textures::Aircraft,"images/Eagle.png");
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
	playerAircraft = leader.get();
	leader->setPosition(spawnPos);
	sceneLayers[Foreground]->attachChild(std::move(leader));
}

void World::fixedUpdate(const float dt)
{
	worldView.setCenter(playerAircraft->getWorldPosition());

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
	for(auto layer : layers)
		window.draw(*layer);
	window.draw(sceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return commandQueue;
}

World::~World()
{
	for(MapLayer* layer : layers)
		delete layer;
	layers.clear();
}

