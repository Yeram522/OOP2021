#pragma once
#include "Behaviour.h"
#include "Transform.h"

class ButtonScript : public Behaviour
{
public:
	ButtonScript(GameObject* obj) : Behaviour(obj){}

	void update() override {
		auto pos = input->getMousePosition();

		
	}


};

