#pragma once
#include "GameObject.h"
#include "Behaviour.h"
#include "Transform.h"
#include "MoveMapScript.h"
#include <vector>


class PlayerMoveScript: public Behaviour
{
	GameObject* map;
	MoveMapScript* mapscript;
	int currnetAnimationClip;

	float currentX;
	float currentY;
	float speed;
	
public:
	PlayerMoveScript(GameObject* gameObject) : Behaviour(gameObject), map(gameObject->getParent()), currentX(0.0f),currentY(10.0f)
	{
		auto pos = transform->getPos();
		auto dim = renderer->getDimension();
		currentX = pos.x;
		currentY = pos.y;
		mapscript = map->getComponent<MoveMapScript>();
	}


	void update() override
	{
		auto shape = renderer->getShape();
		auto pos = transform->getPos();
		auto dim = renderer->getDimension();
		auto width = dim.x;
		auto height = dim.y;

		//renderer->setShape(Animator().shape.c_str());

		if (input->getKey(VK_RIGHT)) {
			float nextX = currentX + 1.0f;
			currentX = nextX;
			/*if (mapScript->isValidRange({ (int)nextX, (int)currentY }, dim))
				currentX = nextX;*/
			return;
		}
		if (input->getKey(VK_LEFT)) {
			float nextX = currentX - 1.0f;
			currentX = nextX;
			/*if (mapScript->isValidRange({ (int)nextX, (int)currentY }, dim))
				currentX = nextX;*/
			return;
		}
		if (input->getKey(VK_UP)) {
			float nextY = currentY - 1.0f;
			currentY = nextY;			
		}

		if (input->getKey(VK_DOWN)) {
			float nextY = currentY + 1.0f;
			currentY = nextY;
		}

		if(currentX != 0)
			currentX -= mapscript->getSpeed();
		transform->setPos(currentX, currentY);
	}
};

