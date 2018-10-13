#pragma once

#include <nclgl\Window.h>
#include <Common\GameObject.h>
#include <Common\EventQueue.h>
#include "Controller.h"
#include "Gamepad.h"
#include "KeyboardController.h"

class Input
{
public:
	Input(Window &w, std::vector<GameObject*>& objects, EventQueue* eq);
	~Input();


	//Subsystem update
	void InputUpdate(float msec);


	//Get subsystem
	GameEnums::Subsystem GetSubsystem() { return GameEnums::Subsystem::Input; }

protected:

	//Pointers that the input needs
	Window* win;
	EventQueue* eQueue;
	std::vector<GameObject*>* obj;
	Controller* con;
	Controller* g;
	Controller* kb;
};

