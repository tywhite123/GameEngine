#include "Event.h"



Event::Event(GameEnums::MType type)
{
	//Assign the event type
	eventType = type;


	//Check what the event was and then assign it the correct subsystems
	if (eventType == GameEnums::MType::Move_Left) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}

	if (eventType == GameEnums::MType::Move_Right) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::Move_Up) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::Move_Down) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::New_Obj) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::Rest) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::Update_Pos_AI) {
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::Attack) {
		subsystems.push_back(GameEnums::Subsystem::Audio);
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::Finish_Level) {
		subsystems.push_back(GameEnums::Subsystem::Audio);
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
	if (eventType == GameEnums::MType::All_Enemies_Dead) {
		subsystems.push_back(GameEnums::Subsystem::Audio);
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}

}

Event::Event(GameEnums::MType type, bool newLvl, float data)
{
	eventType = type;
	levelNew = newLvl;
	this->data = data;

	if (eventType == GameEnums::MType::Finish_Level) {

	}
	if (eventType == GameEnums::MType::New_Level) {
		subsystems.push_back(GameEnums::Subsystem::Physics);
		subsystems.push_back(GameEnums::Subsystem::Graphics);
	}
}


Event::~Event()
{
}
