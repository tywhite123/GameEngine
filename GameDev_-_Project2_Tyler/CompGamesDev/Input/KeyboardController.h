#include <nclgl\Window.h>
#include "Controller.h"


class KeyboardController : public Controller
{
public:
	KeyboardController();
	~KeyboardController();

	//Return if certain keyboard controls have been pressed
	bool up() { return Window::GetKeyboard()->KeyDown(KEYBOARD_W); }
	bool right() { return Window::GetKeyboard()->KeyDown(KEYBOARD_D); }
	bool left() { return Window::GetKeyboard()->KeyDown(KEYBOARD_A); }
	bool down() { return Window::GetKeyboard()->KeyDown(KEYBOARD_S); }
	bool attack() { return Window::GetKeyboard()->KeyTriggered(KEYBOARD_SPACE); }

	bool CheckConnected() { return false; }
	bool Refresh() { return false; }

protected:

};

