#include "TextureReader.h"



TextureReader::TextureReader(std::string texFile, std::vector<std::pair<std::string,std::string>>&textureList)
{
	this->texFile = texFile;

	std::ifstream textures;
	textures.open(texFile);

	std::string name;
	std::string path;

	if (textures) {
		std::string line;

		while (std::getline(textures, line)) {
			std::stringstream split(line);
			int i = 0;
			while (split.good())
			{
				std::string substr;
				std::getline(split, substr, ',');
				
				if (i == 0)
					name = substr;
				else
					path = substr;
				i++;
			}
			
			
			
			textureList.push_back(std::pair<std::string, std::string>(name, path));
		}
	}

	textures.close();
}


TextureReader::~TextureReader()
{
}
