#pragma once

#include <Common\GameObject.h>
#include <Common\EventQueue.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>


class TextureReader
{
public:
	TextureReader(std::string tex, std::vector<std::pair<std::string, std::string>>&textureList);
	~TextureReader();

private:
	std::string texFile;

};

