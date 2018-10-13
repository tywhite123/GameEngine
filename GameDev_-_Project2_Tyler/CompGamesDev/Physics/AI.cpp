#include "AI.h"



AI::AI(std::vector<GameObject*>& objects, b2World &world, EventQueue* eq)
{
	this->world = &world;
	objList = &objects;
	eQueue = eq;
}


AI::~AI()
{
}

void AI::AIUpdate(float msec)
{
	for (auto ob : *objList) {
		if (ob->getType() == ObjectType::Enemy) {
			if (ob->getPos().x == 3.25) {
				
			}
		}
	}
}
