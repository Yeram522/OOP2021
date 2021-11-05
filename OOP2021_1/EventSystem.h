#pragma once

#include <iostream>
#include "Position.h"
#include "Borland.h"
#include <string.h>

using namespace std;

enum class EventType {
	nothing,
	exitGame,
	saveGame,
	loadData
};


class EventSystem
{
	EventType currentEventType;
	EventSystem():currentEventType(EventType::nothing)
	{}	
	static EventSystem* Instance;
public:
	static EventSystem* GetInstance() {
		if (Instance == nullptr) {
			Instance = new EventSystem;
		}
		return Instance;
	}

	EventType getCurrentEvenetType() { return currentEventType; };
	void setCurrentEventType(const EventType eventtype = EventType::nothing) 
	{ currentEventType = eventtype; }


	void startEvent(EventType eventtype)
	{
		switch (eventtype)
		{
		case EventType::exitGame:
			startEvent<EventType::exitGame>();
			break;
		case EventType::saveGame:
			startEvent<EventType::saveGame>();
			break;
		case EventType::loadData:
			startEvent<EventType::loadData>();
			break;
		}
	}

	template <EventType T>
	void startEvent()
	{}

	template <> void startEvent<EventType::exitGame>() 
	{		
		//cout << "extitGameEventStart" << endl;
		currentEventType = EventType::exitGame;
	}
	template <> void startEvent<EventType::saveGame>() 
	{
		//cout << "continueGameEventStart" << endl;
		currentEventType = EventType::saveGame;	
	}
	template <> void startEvent<EventType::loadData>()
	{
		//cout << "continueGameEventStart" << endl;
		currentEventType = EventType::loadData;
	}
};


