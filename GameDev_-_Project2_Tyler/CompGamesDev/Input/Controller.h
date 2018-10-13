#pragma once


class Controller
{
public:
	Controller();
	~Controller();

	//Virtual functions for classes to inherit
	virtual bool up() = 0;
	virtual bool right() = 0;
	virtual bool left() = 0;
	virtual bool down() = 0;
	virtual bool attack() = 0;

	virtual bool Refresh() = 0;
	virtual bool CheckConnected() = 0;

};

