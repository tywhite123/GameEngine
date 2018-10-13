#pragma once

#include <vector>
#include <Common\GameObject.h>
#include <Box2D\Box2D.h>
#include <Common\EventQueue.h>

class AI
{
public:
	AI(std::vector<GameObject*>& objects, b2World &world, EventQueue* eq);
	~AI();

	void AIUpdate(float msec);

private:
	std::vector<GameObject*>* objList;
	b2World* world;
	EventQueue* eQueue;
};

