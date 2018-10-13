#pragma once

#include <iostream>

class Profiling
{
public:
	Profiling();
	~Profiling();

	//update profiler
	void profilerUpdate(float msec, float input, float physics, float graphics, float audio);

private:
	//Profiler information
	float inputTime;
	float audioTime;
	float physicsTime;
	float graphicsTime;

	float timeSinceProfile;
	int framerate;


	float totalTime;

	//float fps;

};

