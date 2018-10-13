#pragma once

#include <Common\GameObject.h>
#include <Common\EventQueue.h>
#include <Common\Game.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

class GameLoader
{
public:
	GameLoader(Game* g, std::string file, std::vector<GameObject*>& objects, EventQueue* eQueue);
	~GameLoader();

	void LoadLevel(std::string gameInfo);

private:

	//Information for game loader
	std::string gameInfo;
	std::vector<GameObject*>* objList;
	EventQueue* eQueue;
	Game* game;
};

