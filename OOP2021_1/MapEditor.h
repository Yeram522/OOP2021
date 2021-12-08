#pragma once
#include "Scene.h"
#include "Button.h"
#include "ButtonScript.h"
#include "SceneManager.h"
#include "MapEditScript.h"
#include "Borland.h"

class MapEditor:public Scene
{
	GameObject* map;
	GameObject* blockCategory;
	MapEditScript* editorScript;
	vector<GameObject*> rootChildren;
public:
	MapEditor(int scenenumber) : Scene(scenenumber) 
	{
		map = new GameObject("map", "panel", nullptr, { 50,20 }, { 5,5 }, Position::zeros, nullptr);
		rootChildren.push_back(map);
		auto panelScript = map->getOrAddComponent<PanelScript>();
		panelScript->setTitle(" screen");
		editorScript = map->getOrAddComponent<MapEditScript>();

		blockCategory = new GameObject("category", "panel", nullptr, { 10,4 }, { 60,5 }, Position::zeros, nullptr);
		rootChildren.push_back(blockCategory);
		panelScript = blockCategory->getOrAddComponent<PanelScript>();
		panelScript->setTitle("category");
	}

	void update() override {

		for (auto child : rootChildren) child->internalUpdate();
		rootChildren.erase(
			std::remove_if(rootChildren.begin(), rootChildren.end(),
				[](auto child) { return child->isActive() == false; }),
			rootChildren.end());
		for (auto child : rootChildren) child->internalRemove();
		for (auto child : rootChildren) child->internalRender();
	}
};

