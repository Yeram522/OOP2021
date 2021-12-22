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

	float currentX;
	float currentY;
	float speed;
	
	Renderer* renderer;
	Renderer* mapRenderer;
public:
	PlayerMoveScript(GameObject* gameObject) : Behaviour(gameObject), map(gameObject->getParent()), currentX(0.0f),currentY(10.0f)
	{
		renderer = gameObject->getComponent<Renderer>();
		mapRenderer = map->getComponent<Renderer>();
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
	
		if (input->getKey(VK_RIGHT)) {
			float nextX = currentX + 1.0f;
			currentX = nextX;
			/*if (!OnCollisionEnter({ (int)nextX+ dim.x, (int)currentY }, dim.y))
				currentX = nextX;*/
			return;
		}
		if (input->getKey(VK_LEFT)) {
			if (currentX <= 0) return;
			float nextX = currentX - 1.0f;
			currentX = nextX;
			/*if (!OnCollisionEnter({ (int)nextX , (int)currentY }, dim.y))
				currentX = nextX;*/
			return;
		}
		if (input->getKey(VK_UP)) {
			float nextY = currentY - 1.0f;
			currentY = nextY;
			/*if (!OnCollisionEnter({ (int)currentX, (int)nextY }, dim.x))
				currentY = nextY;*/
			return;
		}

		if (input->getKey(VK_DOWN)) {
			float nextY = currentY + 1.0f;
			currentY = nextY;
			/*if (!OnCollisionEnter({ (int)currentX, (int)nextY + dim.y }, dim.x))
				currentY = nextY;*/
			return;
		}



		transform->setPos(currentX, currentY);

		Borland::gotoxy(10, 41); printf("PlayerPos : (%d , %d)\n", currentX, currentY);

		
	}
};

