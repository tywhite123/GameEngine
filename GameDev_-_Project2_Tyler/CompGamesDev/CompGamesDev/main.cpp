#include <nclgl\Window.h>
#include <Common\EventQueue.h>
#include <Common\Game.h>
#include <Renderer\Graphics.h>
#include <Physics\Physics.h>
#include <Input\Input.h>
#include <Audio\Audio.h>
#include <FileIO\GameLoader.h>
#include <FileIO\TextureReader.h>
#include <FileIO\GameInfo.h>
#include <Profiler\Profiling.h>


int main() {

	

	//Create a window
	Window w("CSC3224 - Game Engine", 1920, 1080);

	

	//Create a store for the game objects
	Game* game = nullptr;
	vector<GameObject*> gameObjects;
	vector<pair<string, string>> textureList;

	GameInfo("..\\Levels\\Game.csv", game);

	TextureReader(game->getTexturesFile(), textureList);

	//TextureReader("..\\TestLevel\\textures.csv", textureList);
	
	//Create an event queue
	EventQueue* queue = new EventQueue();

	

	string file = game->getLevels();
	int levelNo = game->getCurrentLevel();
	file.append(to_string(levelNo));
	file.append(game->getFileType());

	

	//load the game from csv and give it the game objects vector
	GameLoader loader(game, file, gameObjects, queue);
	//GameLoader loader("..\\TestLevel\\test.csv", gameObjects, queue);

	

	//Create each subsystem and give it what it needs
	Physics physics(gameObjects, queue);
	Graphics graphics(w, gameObjects, queue, textureList);
	Input input(w, gameObjects, queue);
	Audio audio(queue);

	Profiling profiler;

	//int i = 0;
	//bool levelLoaded = true;
	bool lose = false;

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		//get msec
		float msec = w.GetTimer()->GetTimedMS();

		//Update each system and get how long that system took to run
		float currentTime = w.GetTimer()->GetMS();
		input.InputUpdate(msec);
		float inputTime = w.GetTimer()->GetMS() - currentTime;

		currentTime = w.GetTimer()->GetMS();
		audio.AudioUpdate(msec);
		float audioTime = w.GetTimer()->GetMS() - currentTime;

		currentTime = w.GetTimer()->GetMS();
		physics.PhysicsUpdate(msec);
		float physicsTime = w.GetTimer()->GetMS() - currentTime;

		currentTime = w.GetTimer()->GetMS();
		graphics.GraphicsUpdate(msec);
		float graphicsTime = w.GetTimer()->GetMS() - currentTime;
		
		if (!gameObjects.empty()) {
			if (gameObjects.at(0)->getPos().y >= 3.8f && (gameObjects.at(0)->getPos().x >= -2.17 && gameObjects.at(0)->getPos().x <= 2.17)) {
					for (auto* q: queue->getEvents()) {
						queue->popEvent();
					}
				
				queue->pushEvent(new Event(GameEnums::MType::Finish_Level));
			}
			if (gameObjects.at(0)->getHP() <= 0) {
				queue->pushEvent(new Event(GameEnums::MType::Finish_Level));
				lose = true;

			}
		}
		if (gameObjects.empty()) {

			if (game->getCurrentLevel() == game->getNoOfLevels()) {
				loader.LoadLevel("..\\Levels\\Win.csv");
			}
			else{
				if (!lose) {
					game->updateLevel();
				}
				

				string file = game->getLevels();
				int levelNo = game->getCurrentLevel();
				file.append(to_string(levelNo));
				file.append(game->getFileType());

				loader.LoadLevel(file);
			}
			
		}
		

		//i++;
		//Update the profiler with the times of each system
		profiler.profilerUpdate(msec, inputTime, physicsTime, graphicsTime, audioTime);

	}

	for (auto o : gameObjects) {
		delete o;
	}

	//delete objects
	delete queue, gameObjects;
	delete game;

	return 0;
}