#pragma once

#include <iostream>
#include "Position.h"
#include "Borland.h"
#include <string.h>

using namespace std;

enum class EventType {
	nothing,
	exitGame,
	continueGame
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
		case EventType::continueGame:
			startEvent<EventType::continueGame>();
			break;
		}
	}

	template <EventType T>
	void startEvent()
	{}

	template <> void startEvent<EventType::exitGame>() 
	{
		Borland::gotoxy(0, 36);
		cout << "extitGameEventStart" << endl;
		currentEventType = EventType::exitGame;
		Borland::gotoxy(0, 0);
	}
	template <> void startEvent<EventType::continueGame>() 
	{
		Borland::gotoxy(0, 36);
		cout << "continueGameEventStart" << endl;
		currentEventType = EventType::continueGame;
		Borland::gotoxy(0, 0);
	
	}
};


