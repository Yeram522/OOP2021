#pragma once
#include "GameObject.h"
#include "Behaviour.h"
#include "Transform.h"
#include "MoveMapScript.h"
#include <vector>
struct AnimationClip {
	string		shape;
	Dimension	dim;
};

class PlayerMoveScript: public Behaviour
{
	float currentX;
	float currentY;
	float speed;
	GameObject* map;
	MoveMapScript* mapscript;


	int currnetAnimationClip;

public:
	PlayerMoveScript(GameObject* gameObject) : Behaviour(gameObject), map(gameObject->getParent()), currentX(0.0f),currentY(10.0f)
	{
		auto pos = transform->getPos();
		auto dim = renderer->getDimension();
		currentX = pos.x;
		currentY = pos.y;
		mapscript = map->getComponent<MoveMapScript>();
	}

	AnimationClip Animator()
	{
		vector<AnimationClip> clips{
			{ "\xCD\xCD\xCB\xCD\xCD\xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4}	},
			{ "  \xCB  \xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4}  }
		};
		if (currnetAnimationClip == clips.capacity()-1) currnetAnimationClip = 0;//마지막 클립이면 처음클립으로 돌아간다.
		else currnetAnimationClip++;

		return clips[currnetAnimationClip];
	}

	void update() override
	{
		auto shape = renderer->getShape();
		auto pos = transform->getPos();
		auto dim = renderer->getDimension();
		auto width = dim.x;
		auto height = dim.y;

		renderer->setShape(Animator().shape.c_str());

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

