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

	bool isLoaded() { return this->isload; };
	void setLoad(bool trigger) { this->isload = trigger; }
	int getIndex() { return this->buildindex; }
	virtual void update()
	{}
};

