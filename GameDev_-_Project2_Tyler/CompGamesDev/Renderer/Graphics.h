#pragma once
#include <nclgl\Window.h>
#include "Renderer.h"
#include <Common\EventQueue.h>
#include <map>


class Graphics
{
public:
	Graphics(Window &parent, vector<GameObject*>& objects, EventQueue* eq, vector<pair<string, string>>&textureList);
	~Graphics();

	//Update the graphics
	void GraphicsUpdate(float msec);
	
	//New object function which was used for testion
	void NewObject();

	void LoadLevel();


	//Recive events
	void RecieveEvent();

	void CheckEnemiesLeft();

	void UpdateEnemy();


	void Win(GLTtext* &win);

	//Get subsystem
	GameEnums::Subsystem GetSubsystem() { return GameEnums::Subsystem::Graphics; }
	//bool CheckEsc() {
		//Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE);
	//}


	//Window getWindow() { return w; }

private:
	//Window w;
	Renderer r;

	Mesh* m;
	Shader* s;

	std::map<RenderObject*, GameObject*> obj;
	std::vector<GameObject*>* objList;
	EventQueue* eQueue;

	//GLTtext *text;

	bool pushed = false;
	bool tex;

	int a;

	float msec;

	int enemiesLeft;

	float timeToRest;
	bool attack;

	bool doorGone;

	std::map<string, GLuint> textures;

};

