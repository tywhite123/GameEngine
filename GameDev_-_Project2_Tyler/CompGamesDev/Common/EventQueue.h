#pragma once
#include "Event.h"

class EventQueue
{
public:
	EventQueue();
	~EventQueue();

	//Push event to the vector
	void pushEvent(Event* e) {
		events.push_back(e);
	}

	//pop event from the vector
	void removeEvent(int pos) {
		events.erase(events.begin()+pos);
	}

	void popEvent() {
		events.pop_back();
	}

	//get all the events
	std::vector<Event*> getEvents() {
		return events;
	}

protected:

	//vector of events
	std::vector<Event*> events;
};

