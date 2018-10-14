#include "Physics.h"



Physics::Physics(std::vector<GameObject*>& objects, EventQueue* eq) : objList(&objects)
{

	eQueue = eq;

	for (auto ob : objects) {

		if (ob->getType() == ObjectType::Player || ob->getType() == ObjectType::Enemy || ob->getType() == ObjectType::Door) {
			ob->setHP(100);
		}

		if (ob->getType() == ObjectType::Map) {
			continue;
		}

		b2BodyDef bodyDef;

		if (ob->getType() == ObjectType::Player) {
			bodyDef.type = b2_dynamicBody;
		}
		if (ob->getType() == ObjectType::Enemy ) {
			bodyDef.type = b2_dynamicBody;
		}
		if (ob->getType() == ObjectType::Wall || ob->getType() == ObjectType::Door) {
			bodyDef.type = b2_staticBody;
		}


		bodyDef.position.Set(ob->getXPos(), ob->getYPos());
		b2Body* body = world.CreateBody(&bodyDef);

		b2PolygonShape dynamicBox;
			
		if(ob->getType() == ObjectType::Player || ob->getType() == ObjectType::Enemy || ob->getType() == ObjectType::Door)
			dynamicBox.SetAsBox(ob->getScale().x/2, ob->getScale().y/2);
		else if (ob->getType() == ObjectType::Wall && ob->getXPos() > ob->getYPos())
			dynamicBox.SetAsBox((ob->getScale().x / 2), ob->getScale().y / 2);
		else if (ob->getType() == ObjectType::Wall && ob->getXPos() < ob->getYPos())
			dynamicBox.SetAsBox(ob->getScale().x / 2, (ob->getScale().y / 2));
		
			
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		fixtureDef.density = 1.0f;

		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);

		obj.insert(std::pair<GameObject*, b2Body*>(ob, body));
	}

}


Physics::~Physics()
{
}

void Physics::PhysicsUpdate(float msec)
{
	/*RecieveEvent();*/
	//world.Step(timeStep, velocityIterations, positionIterations);
	for (auto ob : *objList) {
		if (ob->getType() == ObjectType::Enemy && ob->getHP() > 0) {
			if (ob->getPos().x > 3.25) {
				/*b2Vec2 vel = obj.at(ob)->GetLinearVelocity();
				vel.x = 0.5f;
				vel.y = 0.0f;
				obj.at(ob)->SetLinearVelocity(vel);*/
				ob->setMovement(0);
			}
			else if (ob->getPos().x < -3.25) {
				/*b2Vec2 vel = obj.at(ob)->GetLinearVelocity();
				vel.x = -0.5f;
				vel.y = 0.0f;
				obj.at(ob)->SetLinearVelocity(vel);*/
				ob->setMovement(1);

			}
			else if (objList->at(0)->getHP() <= 0) {
				ob->setMovement(2);
			}

			if (ob->getMovement() == 0) {
				//ob->setXPos(ob->getPos().x - 0.25f);
				b2Vec2 vel = obj.at(ob)->GetLinearVelocity();
				vel.x = -0.5f;
				vel.y = 0.0f;
				obj.at(ob)->SetLinearVelocity(vel);

			}
			else if (ob->getMovement() == 1) {
				b2Vec2 vel = obj.at(ob)->GetLinearVelocity();
				vel.x = 0.5f;
				vel.y = 0.0f;
				obj.at(ob)->SetLinearVelocity(vel);
				//ob->setXPos(ob->getPos().x + 0.25f);
			}
			else {

			}

		}

	}

	for (int i = 0; i < objList->size(); ++i) {
		for (int j = 0; j < objList->size(); ++j) {
			for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()) {
				if (objList->at(i)->getType() == ObjectType::Enemy && objList->at(j)->getType() == ObjectType::Player) {
					if (contact->GetFixtureB()->GetBody() == obj.at(objList->at(i)) || contact->GetFixtureA()->GetBody() == obj.at(objList->at(i))) {
						if (contact->GetFixtureB()->GetBody() == obj.at(objList->at(j)) || contact->GetFixtureA()->GetBody() == obj.at(objList->at(j))) {
							if (loseHealth >= 1500.0f) {
								objList->at(j)->updateHP(-5);
								loseHealth = 0;
							}

							loseHealth += msec;
						}

					}

				}
			}
		}
	}

	//world.Step(timeStep, velocityIterations, positionIterations);
	//for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()) {
	//	b2Body* A = contact->GetFixtureA()->GetBody();
	//	b2Body* B = contact->GetFixtureA()->GetBody();/*
	//	contact->GetFixtureA()->GetBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	//	contact->GetFixtureA()->GetBody()->SetAngularVelocity(0);*/
	//	contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	//}
	//	}*/

	//	//eQueue->pushEvent(new Event(GameEnums::MType::Update_Pos_AI));
	//


	world.Step(timeStep, velocityIterations, positionIterations);

	b2Vec2 pos;

	for (auto o : obj) {
		b2Vec2 position = o.second->GetPosition();
		pos = position;
		float32 angle = o.second->GetAngle();

		o.first->setXPos(position.x);
		o.first->setYPos(position.y);
		

		
		//printf("%4.2f %4.2f %4.2f\n", o.first->getXPos(), o.first->getYPos(), angle);
		//printf("Enum Val: %d, Health: %d\n", o.first->getType(), o.first->getHP());
	}	

}

void Physics::NewObject()
{
	GameObject* o = new GameObject(rand() % 3, rand() % 3);
	objList->push_back(o);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(o->getXPos(), o->getYPos());
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;

	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	obj.insert(std::pair<GameObject*, b2Body*>(objList->at(objList->size()-1), body));

	printf("New object");
}

void Physics::LoadLevel()
{
	obj.clear();

for (auto ob : *objList) {

		if (ob->getType() == ObjectType::Player || ob->getType() == ObjectType::Enemy || ob->getType() == ObjectType::Door) {
			ob->setHP(100);
		}

		if (ob->getType() == ObjectType::Map) {
			continue;
		}

		b2BodyDef bodyDef;

		if (ob->getType() == ObjectType::Player) {
			bodyDef.type = b2_dynamicBody;
		}
		if (ob->getType() == ObjectType::Enemy) {
			bodyDef.type = b2_dynamicBody;
		}
		if (ob->getType() == ObjectType::Wall || ob->getType() == ObjectType::Door) {
			bodyDef.type = b2_staticBody;
		}


		bodyDef.position.Set(ob->getXPos(), ob->getYPos());
		b2Body* body = world.CreateBody(&bodyDef);

		b2PolygonShape dynamicBox;

		if (ob->getType() == ObjectType::Player || ob->getType() == ObjectType::Enemy || ob->getType() == ObjectType::Door)
			dynamicBox.SetAsBox(ob->getScale().x / 2, ob->getScale().y / 2);
		else if (ob->getType() == ObjectType::Wall && ob->getXPos() > ob->getYPos())
			dynamicBox.SetAsBox((ob->getScale().x / 2), ob->getScale().y / 2);
		else if (ob->getType() == ObjectType::Wall && ob->getXPos() < ob->getYPos())
			dynamicBox.SetAsBox(ob->getScale().x / 2, (ob->getScale().y / 2));


		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		fixtureDef.density = 1.0f;

		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);

		obj.insert(std::pair<GameObject*, b2Body*>(ob, body));
	}
}



void Physics::RecieveEvent()
{

	bool finish = false;
	for (int i = 0; i < eQueue->getEvents().size(); ++i) {
		if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Finish_Level) {
			finish = true;
		}
	}

	for (int i = 0; i < eQueue->getEvents().size(); ++i) {

		if (finish && eQueue->getEvents().at(i)->getType() != GameEnums::MType::Finish_Level) {
			continue;
		}

		for (int j = 0; j < eQueue->getEvents().at(i)->getSubsystems().size(); ++j) { 
			

			if (eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {
				for (int o = 0; o < objList->size(); ++o) {

					if (objList->at(o)->getType() == ObjectType::Player) {
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Left) {
							b2Vec2 vel = obj.at(objList->at(o))->GetLinearVelocity();
							vel.x = -0.5f;
							vel.y = 0.0f;
							obj.at(objList->at(o))->SetLinearVelocity(vel);
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Right) {
							b2Vec2 vel = obj.at(objList->at(o))->GetLinearVelocity();
							vel.x = 0.5f;
							vel.y = 0.0f;
							obj.at(objList->at(o))->SetLinearVelocity(vel);
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Up) {
							b2Vec2 vel = obj.at(objList->at(o))->GetLinearVelocity();
							vel.x = 0.0f;
							vel.y = 0.5f;
							obj.at(objList->at(o))->SetLinearVelocity(vel);
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Down) {
							b2Vec2 vel = obj.at(objList->at(o))->GetLinearVelocity();
							vel.x = 0.0f;
							vel.y = -0.5f;
							obj.at(objList->at(o))->SetLinearVelocity(vel);
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::New_Obj) {
							NewObject();
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Rest) {
							b2Vec2 vel = obj.at(objList->at(o))->GetLinearVelocity();
							vel.x = 0.0f;
							vel.y = 0.0f;
							obj.at(objList->at(o))->SetLinearVelocity(vel);
						}

						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Attack) {
							for (int z = 0; z < objList->size(); ++z) {




								for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()) {
									if (objList->at(z)->getType() == ObjectType::Enemy || objList->at(z)->getType() == ObjectType::Door) {
										if (contact->GetFixtureB()->GetBody() == obj.at(objList->at(z)) || contact->GetFixtureA()->GetBody() == obj.at(objList->at(z))) {
											objList->at(z)->updateHP(-10);

										}

									}
								}

								if (objList->at(z)->getType() == ObjectType::Enemy || objList->at(z)->getType() == ObjectType::Door) {
									if (objList->at(z)->getHP() <= 0) {
   										world.DestroyBody(obj.at(objList->at(z)));
										obj.erase(objList->at(z));
										continue;
									}
								}
							}
						}

					}
				}

				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Finish_Level) {
					/*for (int z = obj.size()-1; z >= 0; --z) {
						world.DestroyBody(obj.at(objList->at(z)));
						obj.erase(objList->at(z));
					}*/

					for (auto ob : obj) {
						world.DestroyBody(ob.second);
					}
					for (int z = obj.size() - 1; z >= 0; --z) {
						obj.erase(objList->at(z));
					}

				}

				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::New_Level) {
					LoadLevel();
						
				}

				if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::All_Enemies_Dead) {
					for (auto ob : *objList) {
						if (ob->getType() == ObjectType::Door) {
							std::string hello;
							world.DestroyBody(obj.at(ob));
							obj.erase(ob);
						}
					}
				}
			


				if (eQueue->getEvents().at(i)->getSubsystems().size() - 1 == j 
					&& eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {
					eQueue->removeEvent(i);
					return;
				}
			}

		}
	}
}
