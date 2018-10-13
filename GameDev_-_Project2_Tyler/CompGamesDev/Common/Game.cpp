#include "Game.h"


Game::Game(int noLevels, std::string textures, std::string levels, std::string filetype, std::vector<int> levelObj)
{
	noOfLevels = noLevels;
	currentLevel = 1;
	this->textures = textures;
	this->levels = levels;
	this->filetype = filetype;
	objPerLevel = levelObj;
}

Game::~Game()
{
}
