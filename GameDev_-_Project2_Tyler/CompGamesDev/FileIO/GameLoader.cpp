#include "GameLoader.h"



GameLoader::GameLoader(Game* g, std::string file, std::vector<GameObject*>& objects, EventQueue* eq)
{
	//Assign the information
	gameInfo = file;
	objList = &objects;
	eQueue = eq;
	game = g;


	//Create a file stream and open the file
	std::ifstream level;
	level.open(gameInfo);

	int noOfHeadings = game->getObjLevel().at(game->getCurrentLevel() - 1);

	//Setup the array for the information
	//std::string testInfo[11][11];
	std::vector<std::vector<std::string>> testInfo(11);
	
	//check if file is open
	if (level) {

		//Get the first line
		std::string firstLine;

		//variable to put in the info in the correct place in the info array
		int line = 0;
		int heading = 0;

		//While you there is a line
		while (std::getline(level, firstLine)) {

			//Split it into each component by the comma
			std::stringstream test(firstLine);
			while (test.good()) {
				std::string substr;
				std::getline(test, substr, ',');
				
				//Stick that into the info array
				//testInfo[heading][line] = substr;
				testInfo[heading].push_back(substr);

				//increment heading
				heading++;

				//if heading is at 9 restart
				if (heading == noOfHeadings)
					heading = 0;
			}

			//increment line
			//line++;

			//if at 10 restart
			/*if (line == 11)
				line = 0;*/
		}

	}

	//Close file
	level.close();


	for (int i = 1; i < testInfo[0].size(); ++i) {
		/*for (int j = 1; j < 9; ++j) {
			

			std::cout << testInfo[j][i] << std::endl;
		}*/
		//for each line create a game object for it
		std::string::size_type sz;
		bool transparent;
		if (testInfo[8][i] == "1")
			transparent = true;
		else
			transparent = false;

		objList->push_back(new GameObject(std::stof(testInfo[2][i],&sz), std::stof(testInfo[3][i], &sz), std::stof(testInfo[4][i], &sz), std::stof(testInfo[5][i], &sz), std::stof(testInfo[6][i], &sz), std::stof(testInfo[7][i], &sz), testInfo[0][i], testInfo[1][i], std::stoi(testInfo[8][i], &sz), testInfo[9][i], testInfo[10][i]));
	}

}


GameLoader::~GameLoader()
{
}

void GameLoader::LoadLevel(std::string gameInfo)
{

	for (auto* o : *objList) {
		delete o;
	}

	objList->clear();

	//Create a file stream and open the file
	std::ifstream level;
	level.open(gameInfo);

	//Setup the array for the information
	//std::string testInfo[11][10];

	std::vector<std::vector<std::string>> testInfo(11);

	//variable to put in the info in the correct place in the info array
	int line = 0;
	int heading = 0;

	//check if file is open
	if (level) {

		//Get the first line
		std::string firstLine;


		//While you there is a line
		while (std::getline(level, firstLine)) {

			//Split it into each component by the comma
			std::stringstream test(firstLine);
			while (test.good()) {
				std::string substr;
				std::getline(test, substr, ',');

				//Stick that into the info array
				testInfo[heading].push_back(substr);

				//increment heading
				heading++;

				//if heading is at 9 restart
				if (heading == 11)
					heading = 0;
			}

			//increment line
			line++;

			////if at 10 restart
			//if (line == 10)
			//	line = 0;
		}

	}

	//Close file
	level.close();


	for (int i = 1; i < line; ++i) {
		/*for (int j = 1; j < 9; ++j) {


		std::cout << testInfo[j][i] << std::endl;
		}*/
		//for each line create a game object for it
		std::string::size_type sz;
		objList->push_back(new GameObject(std::stof(testInfo[2][i], &sz), std::stof(testInfo[3][i], &sz), std::stof(testInfo[4][i], &sz), std::stof(testInfo[5][i], &sz), std::stof(testInfo[6][i], &sz), std::stof(testInfo[7][i], &sz), testInfo[0][i], testInfo[1][i], std::stoi(testInfo[8][i], &sz), testInfo[9][i], testInfo[10][i]));
	}

	eQueue->pushEvent(new Event(GameEnums::MType::New_Level, true, objList->size()));

}
