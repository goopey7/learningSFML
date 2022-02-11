//Copyright Sam Collier 2022
#pragma once

#include <tmxlite/Map.hpp>
#include <vector>
#include "SFMLOrthogonalLayer.h"
#include <array>
#include "CommandQueue.h"
#include "SpriteNode.h"
#include "Aircraft.h"
#include "Hero.h"

class World : private sf::NonCopyable
{
	public:
		explicit World(sf::RenderWindow& window);
		~World();
		void fixedUpdate(const float dt);
		void update(const float dt);
		void draw();
		CommandQueue& getCommandQueue();

	private:
		void loadTextures();
		void buildScene();

		// LayerCount will naturally return the number of layers before it
		// enums start at 0
		enum Layer
		{
			Background,
			Foreground,
			LayerCount
		};

		sf::RenderWindow& window;
		sf::View worldView;
		TextureHolder textures;
		SceneNode sceneGraph;

		// std::array behaves like a C array except it doesn't implicitly evaluate elements
		// as ptrs and adds additional functions such as size()
		std::array<SceneNode*, LayerCount> sceneLayers;

		sf::FloatRect worldBounds;
		sf::Vector2f spawnPos;

		CommandQueue commandQueue;

		std::vector<MapLayer*> tileLayers;
};

