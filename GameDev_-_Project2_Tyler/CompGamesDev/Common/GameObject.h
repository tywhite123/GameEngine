#pragma once

#include <nclgl\Vector2.h>
#include <nclgl\Vector3.h>
#include <string>
#include <Common\Event.h>

//Enum for the object type
enum ObjectType {
	Player, Map, Enemy, Wall, Door, Pit
};


class GameObject
{
public:
	GameObject(float x, float y);
	GameObject(float x, float y, float depth, float rot, float sX, float sY, std::string type, std::string shape, bool transparent, std::string regTex, std::string attackTex);
	~GameObject();


	//Getters and setters for all the object info
	float getXPos() { return objectPos.x; }
	void setXPos(float x) { objectPos.x = x; }

	float getYPos() { return objectPos.y; }
	void setYPos(float y) { objectPos.y = y; }

	float getRotation() { return rotation; }
	void setRotation(float r) { rotation = r; }

	Vector3 getPos() { return objectPos; }

	Vector2 getScale() { return scale; }
	void updateScale(Vector2 s) { scale = s; }

	ObjectType getType() { return objType; }
	
	std::string getTexture() { return texPath; }

	std::string getAttackTex() { return attackTex; }

	std::string getShape() { return shapeType; }

	bool Transparent() { return isTransparent; }

	void setHP(int h) { hp = h; }
	void updateHP(int h) { hp += h; }
	int getHP() { return hp; }

	int getMovement() { return movement; }
	void setMovement(int m) { movement = m; }

	int getAnimate() { return animate; }
	void setAnimate(int a) { animate = a; }
	void updateAnimate() { ++animate; }

protected:
	//Object info variables
	Vector3 objectPos;
	float rotation;
	Vector2 scale;

	ObjectType objType;

	std::string texPath;
	std::string attackTex;

	bool isTransparent;

	std::string shapeType;
	
	int hp;

	int movement;

	int animate;
};

