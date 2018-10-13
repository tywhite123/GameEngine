#pragma once
#include <windows.h>
#include <Xinput.h>
#include "Controller.h"

class Gamepad : public Controller
{
public:
	Gamepad();
	~Gamepad();


	//Bools for checking the controllers condition
	bool IsPressed(WORD button);
	bool IsTriggered(WORD button);
	bool CheckConnected();
	bool Refresh();

	//void vibrate();

	//Get the lx and ly of the left stick
	float getLX() { return LX; }
	float getLY() { return LY; }

	//Returns if the controller buttons are pressed/stick has been moved.
	bool up() { return IsPressed(XINPUT_GAMEPAD_DPAD_UP) || getLY() >= 10000; }
	bool right() { return IsPressed(XINPUT_GAMEPAD_DPAD_RIGHT) || getLX() >= 10000; }
	bool left() { return IsPressed(XINPUT_GAMEPAD_DPAD_LEFT) || getLX() <= -10000; }
	bool down() { return IsPressed(XINPUT_GAMEPAD_DPAD_DOWN) || getLY() <= -10000; }
	bool attack() { return IsTriggered(XINPUT_GAMEPAD_X); }

	XINPUT_STATE getState();

protected:
	//Variable the controller state
	XINPUT_STATE state;

	//The last state
	XINPUT_STATE lastState;

	//Id of the controller
	int controllerID;

	//Floats for the left stick
	float LX;
	float LY;

};

