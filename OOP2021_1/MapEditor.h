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
	GameObject* categPrev;//btn
	GameObject* categNext;//btn
	GameObject* currentBlock;

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

		blockCategory = new GameObject("category", "panel", nullptr, { 10,4 }, { 64,5 }, Position::zeros, nullptr);
		rootChildren.push_back(blockCategory);
		panelScript = blockCategory->getOrAddComponent<PanelScript>();
		panelScript->setTitle("category");

		auto blockShape = editorScript->getCurrentBlock();
		Position pos = { 5,2 };
		currentBlock = new GameObject("currentBlock", "block", &blockShape.shape, { 1,1 },
			blockCategory->getComponent<Transform>()->getPos() + pos, Position::zeros, nullptr);
		rootChildren.push_back(currentBlock);

		categPrev = new GameObject("prevBtn", "button", nullptr, { 3,3 }, { 59,6 }, Position::zeros, nullptr);
		rootChildren.push_back(categPrev);
		auto button = categPrev->getOrAddComponent<Button>();
		button->setText("<");
		auto script = categPrev->getOrAddComponent<ButtonScript>();
		script->onClick = [&]() {		
			editorScript->prevCategoryList();
			Borland::gotoxy(10, 40); printf("categPrev button\n");
		};

		categNext = new GameObject("prevBtn", "button", nullptr, { 3,3 }, { 76,6 }, Position::zeros, nullptr);
		rootChildren.push_back(categNext);
		button = categNext->getOrAddComponent<Button>();
		button->setText(">");
		script = categNext->getOrAddComponent<ButtonScript>();
		script->onClick = [&]() {
			editorScript->nextCategoryList();
			Borland::gotoxy(10, 40); printf("categNext button\n");
		};
	}

	void update() override {

		auto blockShape = editorScript->getCurrentBlock();
		currentBlock->getComponent<Renderer>()->setShape(&blockShape.shape);

		for (auto child : rootChildren) child->internalUpdate();
		rootChildren.erase(
			std::remove_if(rootChildren.begin(), rootChildren.end(),
				[](auto child) { return child->isActive() == false; }),
			rootChildren.end());
		for (auto child : rootChildren) child->internalRemove();
		for (auto child : rootChildren) child->internalRender();
	}
};

