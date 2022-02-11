//Copyright Sam Collier 2022
#pragma once

// Each category will have one bit set to 1
// this allows us to use bitwise OR '|' to combine
// categories
// These are categories for SceneNodes/Actors for dispatching commands
namespace Category
{
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		PlayerAircraft = 1 << 1,
		PlayerHero = 1 << 2,
	};
}
// so for example
// unsigned int allSceneNodes = Category::Scene | Category::PlayerAircraft;
