#include "Graphics.h"
#include "Renderer.h"
#include "RenderObject.h"



Graphics::Graphics(Window &w, vector<GameObject*>& objects, EventQueue* eq, vector<pair<string, string>>&textureList) : r(w, objects), objList(&objects)
{

	for (auto tex : textureList) {
		GLuint t = SOIL_load_OGL_texture(tex.second.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		textures.insert(pair<string, GLuint>(tex.first, t));
	}


	enemiesLeft = 0;
	doorGone = false;

	//Set the event queue
	eQueue = eq;

	//For each game object create a render object
	for (auto ob : objects) {


		if (ob->getType() == ObjectType::Enemy)
			++enemiesLeft;


		////Check the type of object and change shader based on that
		if(ob->getType() == ObjectType::Pit)
			s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"BasicFrag.glsl");

		if (ob->getType() == ObjectType::Player || ob->getType() == ObjectType::Enemy || ob->getType() == ObjectType::Door || ob->getType() == ObjectType::Map || ob->getType() == ObjectType::Wall)
			s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"TexturedFragment.glsl");
	
		if (!s->LinkProgram()) {
			return;
		}

		//Get the shape type and generate the correct mesh
		if (ob->getShape() == "Square")
			m = Mesh::GenerateSquare(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		else if (ob->getShape() == "Quad")
			m = Mesh::GenerateQuad();

		//Check for a texture and apply it if so
		if (ob->getTexture() != "Null") {
			m->SetTexture(textures.at(ob->getTexture()));

			

			if (!m->GetTexture()) {
				return;
			}
			tex = true;
		}
		else {
			m->SetTexture(NULL);
			tex = false;
		}


		//Crete the render object and set position
		RenderObject* o = new RenderObject(m, s);
		o->SetModelMatrix(Matrix4::Translation(ob->getPos()) * Matrix4::Scale(Vector3(ob->getScale().x, ob->getScale().y, ob->getScale().x)));
		r.AddRenderObject(*o);
		r.AddObject(*ob, *o);

	}

	r.SetProjMatrix(Matrix4::Perspective(1, 1000, 1920 / 1080, 45.0f));
	

}

Graphics::~Graphics()
{
	for (auto o : obj) {
		delete o.second;
		o.second = nullptr;
	}
	delete m, s;
}

void Graphics::GraphicsUpdate(float msec)
{

	this->msec = msec;
	//Update
	/*RecieveEvent();*/
	UpdateEnemy();
	CheckEnemiesLeft();
	r.UpdateScene(msec);
	r.RenderScene();
}

void Graphics::NewObject()
{
	RenderObject* o = new RenderObject(m, s);
	o->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(objList->size()-1)->getXPos(), objList->at(objList->size() - 1)->getYPos(), -5)) * Matrix4::Scale(Vector3(0.5f, 0.5f, 0.5f)));
	r.AddRenderObject(*o);
	r.AddObject(*objList->at(objList->size() - 1), *o);
}

void Graphics::LoadLevel()
{
	for (auto ob : *objList) {


		if (ob->getType() == ObjectType::Enemy)
			++enemiesLeft;

		//Check the type of object and change shader based on that
		if (ob->getType() == ObjectType::Pit)
			s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"BasicFrag.glsl");

		if (ob->getType() == ObjectType::Player || ob->getType() == ObjectType::Enemy || ob->getType() == ObjectType::Door || ob->getType() == ObjectType::Map || ob->getType() == ObjectType::Wall)
			s = new Shader(SHADERDIR"basicVert.glsl", SHADERDIR"TexturedFragment.glsl");

		if (!s->LinkProgram()) {
			return;
		}

		//Get the shape type and generate the correct mesh
		if (ob->getShape() == "Square")
			m = Mesh::GenerateSquare(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		else if (ob->getShape() == "Quad")
			m = Mesh::GenerateQuad();

		//Check for a texture and apply it if so
		if (ob->getTexture() != "Null") {
			m->SetTexture(textures.at(ob->getTexture()));

			if (!m->GetTexture()) {
				return;
			}
			tex = true;
		}
		else {
			m->SetTexture(NULL);
			tex = false;
		}

		//Crete the render object and set position
		RenderObject* o = new RenderObject(m, s);
		o->SetModelMatrix(Matrix4::Translation(ob->getPos()) * Matrix4::Scale(Vector3(ob->getScale().x, ob->getScale().y, ob->getScale().x)));
		r.AddRenderObject(*o);
		r.AddObject(*ob, *o);

	}

	doorGone = false;
}

void Graphics::RecieveEvent()
{
	bool newLevelNeeded = false;
	for (int i = 0; i < eQueue->getEvents().size(); ++i) {
		if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::New_Level) {
			newLevelNeeded = true;
		}
	}

	//For each event check the subsystems
	for (int i = eQueue->getEvents().size()-1; i >= 0; --i) {
		//if(eQueue->getEvents().at(i)->getSubsystems())
		if (newLevelNeeded && eQueue->getEvents().at(i)->getType() != GameEnums::MType::New_Level) {
			continue;
		}
		for (int j = 0; j < eQueue->getEvents().at(i)->getSubsystems().size(); ++j) {

			if (eQueue->getEvents().at(i)->Done()) {
				continue;
			}

			for (int o = 0; o < objList->size(); ++o) {

				//if the subsystem is graphics
				if (eQueue->getEvents().at(i)->getSubsystems().at(j) == GetSubsystem()) {

					//Check if the player is the object type
					if (objList->at(o)->getType() == ObjectType::Player) {


						//Handle movement of render object
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Left) {
							r.getRenderObj().at(o)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(o)->getXPos(), objList->at(o)->getYPos(), -10.0f)) * Matrix4::Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f)) * Matrix4::Scale(Vector3(objList->at(o)->getScale().x, objList->at(o)->getScale().y, 0.5f)));
							//objList->at(i)->setRotation(90.0f);

							//Check for scale for animation
							if (a == 3) {
								objList->at(o)->updateScale(Vector2(-objList->at(o)->getScale().x, objList->at(o)->getScale().y));
								a = 0;
							}
							else {
								a++;
							}
							eQueue->getEvents().at(i)->updateDone(true);
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Right) {
							r.getRenderObj().at(o)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(o)->getXPos(), objList->at(o)->getYPos(), -10.0f)) * Matrix4::Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f)) * Matrix4::Scale(Vector3(objList->at(o)->getScale().x, objList->at(o)->getScale().y, 0.5f)));
							//objList->at(i)->setRotation(270.0f);
							if (a == 3) {
								objList->at(o)->updateScale(Vector2(-objList->at(o)->getScale().x, objList->at(o)->getScale().y));
								a = 0;
							}
							else {
								a++;
							}
							eQueue->getEvents().at(i)->updateDone(true);
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Up) {
							r.getRenderObj().at(o)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(o)->getXPos(), objList->at(o)->getYPos(), -10.0f)) * Matrix4::Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f)) * Matrix4::Scale(Vector3(objList->at(o)->getScale().x, objList->at(o)->getScale().y, 0.5f)));
							//objList->at(i)->setRotation(0.0f);
							if (a == 3) {
								objList->at(o)->updateScale(Vector2(-objList->at(o)->getScale().x, objList->at(o)->getScale().y));
								a = 0;
							}
							else {
								a++;
							}
							eQueue->getEvents().at(i)->updateDone(true);
						}
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Move_Down) {
							r.getRenderObj().at(o)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(o)->getXPos(), objList->at(o)->getYPos(), -10.0f)) * Matrix4::Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f)) * Matrix4::Scale(Vector3(objList->at(o)->getScale().x, objList->at(o)->getScale().y, 0.5f)));
							//objList->at(i)->setRotation(180.0f);
							if (a == 3) {
								objList->at(o)->updateScale(Vector2(-objList->at(o)->getScale().x, objList->at(o)->getScale().y));
								a = 0;
							}
							else {
								a++;
							}
							eQueue->getEvents().at(i)->updateDone(true);
						}

						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Rest) {
							for (int z = 0; z < objList->size(); ++z) {
								if (objList->at(z)->getType() == ObjectType::Player && timeToRest >= 500.0f) {
									r.getRObj(*objList->at(z)).GetMesh()->SetTexture(textures.at(objList->at(z)->getTexture()));
									attack = false;
									timeToRest = 0;
								}
							}
							eQueue->getEvents().at(i)->updateDone(true);
						}

						//Check if atteck
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Attack) {
							for (int z = 0; z < objList->size(); ++z) {

								if (objList->at(z)->getType() == ObjectType::Player) {
									r.getRObj(*objList->at(z)).GetMesh()->SetTexture(textures.at(objList->at(z)->getAttackTex()));
									attack = true;
								}

								//Check object type is the enemy or door
								if (objList->at(z)->getType() == ObjectType::Enemy) {

									//get its current hp and delete if it is dead
									if (objList->at(z)->getHP() <= 0) {
										r.removeRenderObj(objList->at(z));
										objList->erase(objList->begin() + z);
										enemiesLeft--;
										continue;
									}
								}
							}
							eQueue->getEvents().at(i)->updateDone(true);
						}

					}


					if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::New_Obj) {
						NewObject();
						eQueue->getEvents().at(i)->updateDone(true);
					}

					//If it is an enemy update its pos based on if its pushed
					if (objList->at(o)->getType() == ObjectType::Enemy) {
						if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Update_Pos_AI) {
							/*r.getRenderObj().at(1)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(1)->getXPos(), objList->at(1)->getYPos(), -10.0f)));*/
							pushed = true;
							eQueue->getEvents().at(i)->updateDone(true);
						}

						if (pushed) {
							r.getRenderObj().at(o)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(o)->getXPos(), objList->at(o)->getYPos(), -10.0f)) * Matrix4::Scale(Vector3(0.25f, 0.5f, 0.5f)));
						}
					}


				}

				

				//pop event
				/*if (eQueue->getEvents().at(i)->getSubsystems().size() - 1 == j) {
					eQueue->removeEvent(i);
					if (eQueue->getEvents().empty()) {
						return;
					}
				}*/
			}

			if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::Finish_Level) {
				for (int z = 0; z < objList->size(); ++z) {
					r.removeRenderObj(objList->at(z));

				}
				objList->clear();
				eQueue->getEvents().at(i)->updateDone(true);
			}

			if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::New_Level) {
				LoadLevel();
				std::cout << "here" << std::endl;
				eQueue->getEvents().at(i)->updateDone(true);
			}

			if (eQueue->getEvents().at(i)->getType() == GameEnums::MType::All_Enemies_Dead) {
				for (int z = 0; z < objList->size(); ++z) {
					if (objList->at(z)->getType() == ObjectType::Door) {
						r.removeRenderObj(objList->at(z));
						objList->erase(objList->begin() + z);

					}
				}
				eQueue->getEvents().at(i)->updateDone(true);

			}
			
			if (attack = true) {
					timeToRest += msec;
				}

		}
	}

	for (int i = eQueue->getEvents().size() - 1; i >= 0; --i) {
		//if(eQueue->getEvents().at(i)->getSubsystems())	
			if (eQueue->getEvents().at(i)->Done()) {
				eQueue->removeEvent(i);
				if (eQueue->getEvents().empty()) {
					return;
				}
			}
		//}
	}
}

void Graphics::CheckEnemiesLeft()
{
	if (enemiesLeft == 0 && !doorGone) {
		eQueue->pushEvent(new Event(GameEnums::MType::All_Enemies_Dead));
		doorGone = true;
	}
}

void Graphics::UpdateEnemy()
{
	for (int i = 0; i < objList->size(); ++i) {
		if (ObjectType::Enemy == objList->at(i)->getType()) {
			if (objList->at(i)->getAnimate() >= 3) {
				objList->at(i)->updateScale(Vector2(-objList->at(i)->getScale().x, objList->at(i)->getScale().y));
				objList->at(i)->setAnimate(0);
			}
			else {
				objList->at(i)->updateAnimate();
			}

			r.getRenderObj().at(i)->SetModelMatrix(Matrix4::Translation(Vector3(objList->at(i)->getXPos(), objList->at(i)->getYPos(), -10.0f))
				* Matrix4::Rotation(0.0f, Vector3(0.0f, 0.0f, 1.0f))
				* Matrix4::Scale(Vector3(objList->at(i)->getScale().x, objList->at(i)->getScale().y, 0.5f)));
		}
	}
}


