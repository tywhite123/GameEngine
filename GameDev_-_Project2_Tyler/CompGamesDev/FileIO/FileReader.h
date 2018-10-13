#pragma once

#include <Common\GameObject.h>
#include <vector>;

class FileReader
{
public:
	FileReader(std::string gameInfo, std::vector<GameObject*>& objects);
	~FileReader();

private:
	std::string gameInfo;
	std::vector<GameObject*>* objList;
};

