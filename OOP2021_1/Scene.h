#pragma once
#include <iostream>
#include <string>
#include "Position.h"
#include "GameObject.h"
#include "RendererEnabler.h"


using namespace std;


class Scene
{
	int buildindex;
	bool isload;

public:
	Scene(int buildindex): isload(false)
	{
		this->buildindex = buildindex;
	}

	bool isLoaded() { return isload; };
	void setLoad(bool trigger) { isload = trigger; }

	virtual void update()
	{}
};

