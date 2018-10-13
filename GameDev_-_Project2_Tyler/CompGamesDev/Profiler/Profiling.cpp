#include "Profiling.h"



Profiling::Profiling()
{
	//Initialise everything
	timeSinceProfile = 0;
	audioTime = 0;
	inputTime = 0;
	physicsTime = 0;
	graphicsTime = 0;
	framerate = 0;
	totalTime = 0;
}


Profiling::~Profiling()
{
}

void Profiling::profilerUpdate(float msec, float input, float physics, float graphics, float audio)
{
	//Assign the info
	audioTime = audio;
	inputTime = input;
	physicsTime = physics;
	graphicsTime = graphics;

	//Get total time
	totalTime = audioTime + inputTime + physicsTime + graphicsTime;
	
	//Setup time since last profile and increment framerate
	timeSinceProfile += msec;
	framerate++;

	//check if it has been 1 second
	if (timeSinceProfile >= 1000.0f) {
		
		//Clear the console
		system("cls");

		//Output the information
		std::cout << "Framerate:\t" << framerate << "\n"
			<< "Audio Time:\t" << audioTime << "\n"
			<< "Input Time:\t" << inputTime << "\n"
			<< "Physics Time:\t" << physicsTime << "\n"
			<< "Graphics Time:\t" << graphicsTime << "\n"
			<< "Total time:\t" << totalTime << "\n";

		std::cout << "\n\nControls: " << "\n"
			<< "Up:\nKeyboard: W, \tXbox: Up on DPad or Left Stick\n"
			<< "Down:\nKeyboard: S, \tXbox: Down on DPad or Left Stick\n"
			<< "Left:\nKeyboard: A, \tXbox: Left on DPad or Left Stick\n"
			<< "Right:\nKeyboard: D, \tXbox: Right on DPad or Left Stick\n"
			<< "Attack:\nKeyboard: Space, \tXbox: X on DPad or Left Stick\n";

		//Set to 0;
		timeSinceProfile = 0.0f;
		framerate = 0;

	}
}

