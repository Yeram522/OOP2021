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
		renderer = gameObject->getComponent<Renderer>();//������ ����
	}


	bool OnCollisionEnter(const Position& nextPos, const Dimension& sz)
	{
		auto pos = gameObject->getTransform()->getPosition(); //�ڽ��� ��ġ������ �����´�
		//������ �� �����̸� �� �������� �޾ƿðŴϱ�, �ű⿡ ����� �ִ��� Ȯ���ϸ� ��.
		if (renderer->getShape(nextPos) == '\xDB' || renderer->getShape(nextPos) == '\xB2' || renderer->getShape(nextPos) == '\xB0')
		{
			Borland::gotoxy(10, 41); printf("Collision trigger!! : %d %d\n", nextPos.x, nextPos.y);
			return true;
		}
			
		return false;
	}
};

