#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "Behaviour.h"
#include "Position.h"
#include "Renderer.h"
typedef int strong;

struct BlockShapes {
	char		shape;
	strong        strong;
};

class MapEditScript :
    public Behaviour
{
	const vector<BlockShapes> candidates{
			{ '\xDB',3},
			{ '\xB2',2 },		
			{ '\xB1',1 }
	};

	vector<BlockShapes*> mapdesign;
public:
    MapEditScript(GameObject* gameObject) : Behaviour(gameObject)
    {

    }

	void update() override
	{
		if (!input->getMouseButtonDown(0)) return;
		auto pos = input->getMousePosition();
		if(transform->getPosition().x<pos.x && pos.x<transform->getPosition().x+renderer->getDimension().x
			&& transform->getPosition().y < pos.y && pos.y < transform->getPosition().y + renderer->getDimension().y)
		{
			const char shape = candidates[0].shape;
			renderer->setShape(shape, transform->world2Local(pos));
			Borland::gotoxy(10, 40); printf("buttonClcikc:%d\n"); cout << pos;
		}
	}
};

