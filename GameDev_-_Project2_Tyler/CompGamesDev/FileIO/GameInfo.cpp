#include "GameInfo.h"

GameInfo::GameInfo(string gameFile, Game * &game)
{
	ifstream g;
	g.open(gameFile);

	//string gameInfo[2][8];
	vector<string> gameInfo;

	if (g) {
		string fileLine;

		string name;
		string info;

		while (getline(g, fileLine)) {
			
			stringstream split(fileLine);

			int i = 0;

			while (split.good()) {
				string substr;
				getline(split, substr, ',');

				//gameInfo[heading][line];

				if (i == 0)
					name = substr;
				else
					info = substr;

				i++;


			}

			gameInfo.push_back(info);

		}
		

	}

	g.close();

	vector<int> objPerLevel;
	string::size_type sz;

	for (int i = 4; i < gameInfo.size(); ++i) {
		objPerLevel.push_back(stoi(gameInfo[i], &sz));
	}

	game = new Game(stoi(gameInfo[0], &sz), gameInfo[1], gameInfo[2], gameInfo[3], objPerLevel);



}

GameInfo::~GameInfo()
{
}
