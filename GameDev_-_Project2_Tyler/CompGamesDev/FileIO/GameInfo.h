#pragma once

#include <Common\Game.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

class GameInfo
{
public:
	GameInfo(std::string gameFile, Game* &game);
	~GameInfo();
};

