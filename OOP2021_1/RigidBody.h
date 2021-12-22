#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Renderer.h"

struct edgePosition {
	Direction dir; //����
	Position  pos; //�����ڸ� ��ġ
};

class RigidBody : public Component 
{
	vector<edgePosition> rightedges;
	vector<edgePosition> leftedges;
	vector<edgePosition> upedges;
	vector<edgePosition> downedges;

	Dimension dim;//gameObject�� �����ִ� sprite�� dim
	string sprite; //��������Ʈ ����
protected:
	Renderer* renderer;
public:
	RigidBody(GameObject* gameObject) : Component(gameObject)
	{
		renderer = gameObject->getComponent<Renderer>();//������ ����

		dim = renderer->getDimension();
		sprite = renderer->getShape();

		init();
	}

	void init() //��������Ʈ �����ڸ� ������ٵ� ���� ����.
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


	//������ ��! worldpos�� �ƴ� localpos�� ����Ǿ�������!!
	vector<edgePosition> getEdges(Direction dir) //�ݶ��̴����� �� ������ٵ� ������ �����ͼ� �浹üũ�� �� ����.
	{
		if (dir == Direction::right) return rightedges;
		else if (dir == Direction::left) return leftedges;
		else if (dir == Direction::up) return upedges;
		else if (dir == Direction::down) return downedges;
	}


};

