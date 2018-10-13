#pragma once

#include <Common\GameObject.h>
#include <vector>

class GameSaver
{
public:
	GameSaver(std::string gameSave, std::vector<GameObject*>& objects);
	~GameSaver();

private:
	std::string gameInfo;
	std::vector<GameObject*>* objList;
};

