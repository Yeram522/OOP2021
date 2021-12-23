#pragma once
#include "GameObject.h"
#include "Behaviour.h"
#include "Transform.h"
#include "MoveMapScript.h"
#include "Collider.h"
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

	Collider* collider;
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
		collider = gameObject->getComponent<Collider>();
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
			//currentX = nextX;
			if (collider->OnCollisionEnter(Position::right))
			{
				
				Borland::gotoxy(10, 39); printf("Collide!! : (%f , %f)\n", currentX, currentY);
				return;
			}
			currentX = nextX;
			return;
		}
		if (input->getKey(VK_LEFT)) {
			if (currentX <= 0) return;
			float nextX = currentX - 1.0f;
			
			if (collider->OnCollisionEnter(Position::left))
			{

				Borland::gotoxy(10, 39); printf("Collide!! : (%f , %f)\n", currentX, currentY);
				return;
			}
			currentX = nextX;
			return;
		}
		if (input->getKey(VK_UP)) {
			float nextY = currentY - 1.0f;
			
			if (collider->OnCollisionEnter(Position::up))
			{

				Borland::gotoxy(10, 39); printf("Collide!! : (%f , %f)\n", currentX, currentY);
				return;
			}
			currentY = nextY;
			return;
		}

		if (input->getKey(VK_DOWN)) {
			float nextY = currentY + 1.0f;
			
			if (collider->OnCollisionEnter(Position::down))
			{

				Borland::gotoxy(10, 39); printf("Collide!! : (%f , %f)\n", currentX, currentY);
				return;
			}
			currentY = nextY;
			return;
		}



		transform->setPos(currentX, currentY);

		Borland::gotoxy(10, 41); printf("PlayerPos : (%d , %d)\n", currentX, currentY);

		
	}
};

