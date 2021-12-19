#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Renderer.h"

class Collider: public Component
{
protected:
	Renderer* renderer;
public:
	Collider(GameObject* gameObject) : Component(gameObject)
	{
		renderer = gameObject->getComponent<Renderer>();//랜더러 참조
	}


	bool OnCollisionEnter(const Position& nextPos, const Dimension& sz)
	{
		auto pos = gameObject->getTransform()->getPosition(); //자신의 위치정보를 가져온다
		//왼쪽을 갈 예정이면 그 포지션을 받아올거니까, 거기에 블록이 있는지 확인하면 됨.
		if (renderer->getShape(nextPos) == '\xDB' || renderer->getShape(nextPos) == '\xB2' || renderer->getShape(nextPos) == '\xB0')
		{
			Borland::gotoxy(10, 41); printf("Collision trigger!! : %d %d\n", nextPos.x, nextPos.y);
			return true;
		}
			
		return false;
	}
};

