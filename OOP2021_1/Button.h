#pragma once
#include "GameObject.h"

class Button :public GameObject
{	
	EventType eventtype;
public:
	Button(const Position& pos,const EventType eventtype,GameObject* parent)
		: GameObject("", pos, { parent->getDimension().x,parent->getDimension().y}, parent), eventtype(eventtype)
	{}

	bool isClicked() // check isclicked in range of botton obj
	{
		if (this->local2Screen().x <= input->getMousePosition().x && input->getMousePosition().x <= this->local2Screen().x + this->getDimension().x
			&& this->local2Screen().y <= input->getMousePosition().y && input->getMousePosition().y <= this->local2Screen().y + this->getDimension().y)
			return true;

		return false;
	}

	void update() override
	{
		if (input->getMouseButtonDown(0)&& isClicked())
		{
			eventsystem->startEvent(eventtype);
		}
	}
};