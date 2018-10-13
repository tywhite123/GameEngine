#include "Input.h"

Input::Input(Window & w, std::vector<GameObject*>& objects, EventQueue* eq)
{
	win = &w;
	obj = &objects;
	eQueue = eq;

	//Create the controller objects
	g = new Gamepad();
	kb = new KeyboardController();

	//Check to see if gamepad is connected before deciding what controller to use
	if (g->CheckConnected()) {
		con = g;
	}
	else {
		con = kb;
	}
	
}

Input::~Input()
{
	delete kb, g;
	con = g = kb = nullptr;
}

void Input::InputUpdate(float msec)
{
	//Refresh the gamepad
	g->Refresh();

	//Check if the gamepad is connected to and change controller accordingly
	if (g->CheckConnected()) {
		con = g;
	}
	else {
		con = kb;
	}

	//Calls the control functions based on what the controller is
	if (con->up()) {
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Up));
	}
	else if (con->down()) {
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Down));
	}
	else if (con->left()) {
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Left));
	}

	else if (con->right()) {
		eQueue->pushEvent(new Event(GameEnums::MType::Move_Right));
	}
	else if (con->attack()) {
		eQueue->pushEvent(new Event(GameEnums::MType::Attack));
	}
	else {
		eQueue->pushEvent(new Event(GameEnums::MType::Rest));
	}

}