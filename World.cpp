//Copyright Sam Collier 2022

#include "World.h"


World::World(sf::RenderWindow& window)
	: window(window),
	worldView(window.getDefaultView()),
	worldBounds(0.f,0.f,2000.f,2000.f),
	spawnPos(worldBounds.width / 2.f,worldBounds.height / 2.f)
{
	loadTextures();
	buildScene();
	worldView.setCenter(spawnPos);
}

void World::loadTextures()
{
	textures.load(Textures::Aircraft,"images/Eagle.png");
	textures.load(Textures::Desert,"images/Desert.png");
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

	// Background
	sf::Texture &bkgTexture = textures.get(Textures::Desert);
	bkgTexture.setRepeated(true);
	sf::IntRect textureRect(worldBounds);
	std::unique_ptr<SpriteNode> bkg(new SpriteNode(bkgTexture,textureRect));
	bkg->setPosition(worldBounds.left,worldBounds.top);
	sceneLayers[Background]->attachChild(std::move(bkg));

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
	window.draw(sceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return commandQueue;
}

