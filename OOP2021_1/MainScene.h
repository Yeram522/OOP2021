#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"

class MainScene : Scene
{
	GameObject* startBtn;
	GameObject* editBtn;

	vector<GameObject*> rootChildren;
protected:
	SceneManager* sceneManager;
public:
	MainScene(int scenenumber) : Scene(scenenumber){
		startBtn = new GameObject("StartBtn", "button", nullptr, { 10,3 }, { 35,25 }, Position::zeros, nullptr);
		rootChildren.push_back(startBtn);
		auto button = startBtn->getOrAddComponent<Button>();
		button->setText("Start");


		editBtn = new GameObject("EditBtn", "button", nullptr, { 10,3 }, { 35,30 }, Position::zeros, nullptr);
		rootChildren.push_back(editBtn);
		button = editBtn->getOrAddComponent<Button>();
		button->setText("Edit");
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

