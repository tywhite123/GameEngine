#pragma once
#include <string>
#include <vector>

class Game
{
public:
	Game(int noLevels, std::string textures, std::string levels, std::string filetype,
		std::vector<int> levelObj);
	~Game();

	int getNoOfLevels() { return noOfLevels; }
	int getCurrentLevel() { return currentLevel; }
	std::string getTexturesFile() { return textures; }
	std::string getLevels() { return levels; }
	std::string getFileType() { return filetype; }
	std::vector<int> getObjLevel() { return objPerLevel; }

	void updateLevel() { ++currentLevel; }

private:
	int noOfLevels;
	int currentLevel;
	std::string textures;
	std::string levels;
	std::string filetype;
	std::vector<int> objPerLevel;

};

