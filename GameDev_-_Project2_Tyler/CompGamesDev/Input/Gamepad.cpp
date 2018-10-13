#include "Gamepad.h"
#include <stdio.h>
#include <math.h>


Gamepad::Gamepad()
{
}


Gamepad::~Gamepad()
{
}

bool Gamepad::IsPressed(WORD button)
{
	//return if the button is pressed
	return (getState().Gamepad.wButtons & button) != 0;
}

bool Gamepad::IsTriggered(WORD button)
{

	return IsPressed(button) && (lastState.Gamepad.wButtons != state.Gamepad.wButtons);
}

bool Gamepad::CheckConnected()
{

	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
		//Create the state
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		//get the state of the controller
		dwResult = XInputGetState(i, &state);
		if(dwResult == ERROR_SUCCESS){
			//printf("Controller Connected in port %d", i);
			controllerID = i;
		}
		else{
		}
	}
	return controllerID != -1;
}

bool Gamepad::Refresh()
{

	lastState = state;

	//CHeck if controller is connected
	if (controllerID == -1) {
		CheckConnected();
	}

	//Reset the contollers state
	if (controllerID != -1) {
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(controllerID, &state) != ERROR_SUCCESS) {
			controllerID = -1;
			return false;
		}

		//Left stick from the microsoft documentation on using xinput, code see - https://msdn.microsoft.com/en-us/library/windows/desktop/ee417001(v=vs.85).aspx
		//get the state of the left stick
		LX = state.Gamepad.sThumbLX;
		LY = state.Gamepad.sThumbLY;

		//get the magnitude
		float mag = sqrt(LX*LX + LY*LY);

		//get the values for the stick normalised
		float normalisedLX = LX / mag;
		float normalisedLY = LY / mag;

		float normalisedMag = 0;

		//Check the mag is in the deadzone
		if (mag > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {

			if (mag > 32767) mag = 32767;

			mag -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

			normalisedMag = mag / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

		}
		else {
			mag = 0.0;
			normalisedMag = 0.0;
		}

		//Code for controller vibration
		//XINPUT_VIBRATION vibration;
		//ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		//vibration.wLeftMotorSpeed = 65535; // use any value between 0-65535 here
		//vibration.wRightMotorSpeed = 65535; // use any value between 0-65535 here
		//XInputSetState(0, &vibration);

		//printf("Left Stick LX: %f\nLeft Stick LY: %f\nMagnitude: %f\n", normalisedLX, normalisedLY, normalisedMag);
		//printf("Left Stick LX: %f\nLeft Stick LY: %f\nMagnitude: %f\n", LX, LY, mag);

		

		return true;
	}
	return false;
}

XINPUT_STATE Gamepad::getState()
{
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	XInputGetState(controllerID, &state);
	return state;
}

//void Gamepad::vibrate()
//{
//	XINPUT_VIBRATION vibration;
//	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
//	vibration.wLeftMotorSpeed = 65535; // use any value between 0-65535 here
//	vibration.wRightMotorSpeed = 65535; // use any value between 0-65535 here
//	XInputSetState(0, &vibration);
//
//}
