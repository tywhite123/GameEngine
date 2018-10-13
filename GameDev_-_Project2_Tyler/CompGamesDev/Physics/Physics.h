#pragma once

#include <Box2D\Box2D.h>
#include <map>
#include <vector>
#include <iostream>
#include <Common\GameObject.h>
#include <Common\EventQueue.h>

class Physics
{
public:
	Physics(std::vector<GameObject*>& objects, EventQueue* eq);
	~Physics();

	void PhysicsUpdate(float msec);
	void NewObject();
	void LoadLevel();

	void RecieveEvent();


	//Returns what Subsystem this is
	GameEnums::Subsystem GetSubsystem() { return GameEnums::Subsystem::Physics; }


protected:

	//Setup for the physics box2d world
	b2Vec2 gravity = b2Vec2(0.0, 0.0f);
	b2World world = b2World(gravity);

	//b2ContactListener contactListener;

	//Storage for the bodys and can access with a game object
	std::map<GameObject*, b2Body*> obj;

	//Pointer to a list of all the game objects
	std::vector<GameObject*>* objList;

	//Pointer to the event queue
	EventQueue* eQueue;

	//World step setup
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	float time;
	float loseHealth = 0;
};