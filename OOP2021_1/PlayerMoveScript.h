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

	bool OnCollisionEnter(const char* shape, const Position& pos, const Dimension& dim, bool direction)
	{
		Borland::gotoxy(10, 41); cout << "Player Position:"<< pos << endl;
		Position newpos = pos;
		//direction == true ? newpos.x += dim.x : newpos.y += dim.y;//true이면 수평이동 이므로 넓이를 더해준다.
		if (direction)  newpos.x += 5;
		else
			newpos.y += 4;
		int width = (direction == true ? 4 : 5);

		Borland::gotoxy(10, 42); printf("Searching Position : ");
		for (int i = 0; i < width; i++)
		{
			Position  tmp = transform->local2World({ newpos.x, newpos.y + i });
			Borland::gotoxy(10+i*9, 43);
			printf("(%d,%d)", tmp.x, tmp.y);
			Borland::gotoxy(10, 39);
			printf("         %c\n", shape[mapRenderer->pos2Offset(transform->local2World({ newpos.x, newpos.y + i }))]);
			if (shape[mapRenderer->pos2Offset(transform->local2World({ newpos.x, newpos.y + i }))] == '\xDB' || shape[mapRenderer->pos2Offset(transform->local2World({ newpos.x, newpos.y + i }))] == '\xB2' || shape[mapRenderer->pos2Offset(transform->local2World({ newpos.x, newpos.y + i }))] == '\xB0')
			{
				Borland::gotoxy(10, 39); 
				printf("capture: %c\n", shape[mapRenderer->pos2Offset(transform->local2World({ newpos.x, newpos.y + i }))]);

				return true;
			}
				
		}
		Borland::gotoxy(10, 40); 
		//printf("%c\n", shape[mapRenderer->pos2Offset(newpos)]);
		
		
		
		return false;
		
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


		if (!OnCollisionEnter(shape, { (int)currentX, (int)currentY }, dim, true))
			transform->setPos(currentX, currentY);

		

		
	}
};

