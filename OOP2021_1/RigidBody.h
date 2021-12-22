#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Renderer.h"

struct edgePosition {
	Direction dir; //방향
	Position  pos; //가장자리 위치
};

class RigidBody : public Component 
{
	vector<edgePosition> rightedges;
	vector<edgePosition> leftedges;
	vector<edgePosition> upedges;
	vector<edgePosition> downedges;

	Dimension dim;//gameObject가 갖고있는 sprite의 dim
	string sprite; //스프라이트 정보
protected:
	Renderer* renderer;
public:
	RigidBody(GameObject* gameObject) : Component(gameObject)
	{
		renderer = gameObject->getComponent<Renderer>();//랜더러 참조

		dim = renderer->getDimension();
		sprite = renderer->getShape();

		init();
	}

	void init() //스프라이트 가장자리 리지드바디 라인 생성.
	{	
		for (int i = 0; i < sprite.size()-1; i++)
		{
			//right edge
			if((i+1)%dim.x == 0 && sprite[i] != ' ') rightedges.push_back({ Direction::right,renderer->offset2Pos(i) });
			else if(sprite[i+1]==' ') rightedges.push_back({ Direction::right,renderer->offset2Pos(i + 1) });

			//left edge
			if ((i+dim.x) % dim.x == 0 && sprite[i] != ' ') leftedges.push_back({ Direction::left,renderer->offset2Pos(i) });
			else if (sprite[i - 1] == ' ') leftedges.push_back({ Direction::left,renderer->offset2Pos(i - 1) });

			//up edge
			if (i%dim.x < dim.x && sprite[i] != ' ') upedges.push_back({ Direction::up,renderer->offset2Pos(i) });

			//down edge
			if (i >=dim.x*(dim.y-1) && sprite[i] != ' ') downedges.push_back({ Direction::down,renderer->offset2Pos(i) });
		}

		Borland::gotoxy(10, 41); printf("Debug delay\n");
		
	}


	//주의할 점! worldpos가 아닌 localpos로 저장되어져있음!!
	vector<edgePosition> getEdges(Direction dir) //콜라이더에서 이 리지드바디 정보를 가져와서 충돌체크를 할 예정.
	{
		if (dir == Direction::right) return rightedges;
		else if (dir == Direction::left) return leftedges;
		else if (dir == Direction::up) return upedges;
		else if (dir == Direction::down) return downedges;
	}


};

