#pragma once
#include "GameObject.h"

class ConfirmationPanel :public GameObject
{
public:
	ConfirmationPanel(const Position& pos, GameObject* parent)
		: GameObject(" ",pos , Dimension{ 20, 10 }, parent)
	{
		GameObject::setShape();
	}
};
