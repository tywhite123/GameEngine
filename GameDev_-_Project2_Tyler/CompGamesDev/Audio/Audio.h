#pragma once

#include <fmod.hpp>
#include <Common\EventQueue.h>

class Audio
{
public:
	Audio(EventQueue* eq);
	~Audio();

	void AudioUpdate(float msec);

	void RecieveEvent();

	GameEnums::Subsystem GetSubsystem() { return GameEnums::Subsystem::Audio; }

private:

	//Pointer to a list of events
	EventQueue* eQueue;
	
	//FMOD Variables
	FMOD::System *system;
	FMOD::Sound *ambience;
	FMOD::Sound *sword;
	FMOD::Sound *door;
	FMOD::Channel *channel = 0;
	FMOD_RESULT result;
	unsigned int version;
	void *extradriverdata = 0;

	//A check bool for if anything is playing
	bool playing = false;
	bool playAmbience = false;
	bool playDoor = false;
};

