#pragma once
#include "Scene.h"
#include "Button.h"
#include "ButtonScript.h"
#include "SceneManager.h"
#include "Borland.h"

class MainScene : Scene
{
	GameObject* startBtn;
	GameObject* editBtn;

	vector<GameObject*> rootChildren;
protected:
	SceneManager* sceneManager;
public:
	MainScene(int scenenumber) : Scene(scenenumber){
		startBtn = new GameObject("Start", "button", nullptr, { 10,3 }, { 35,25 }, Position::zeros, nullptr);
		rootChildren.push_back(startBtn);
		auto button = startBtn->getOrAddComponent<Button>();
		button->setText("Start");
		auto script = startBtn->getOrAddComponent<ButtonScript>();
		script->onClick = []() {/*sceneManager->enableSceneinIndex(2);*/
			Borland::gotoxy(10, 40); printf("buttonClcikc\n");
		};
		

		editBtn = new GameObject("Edit", "button", nullptr, { 10,3 }, { 35,30 }, Position::zeros, nullptr);
		rootChildren.push_back(editBtn);
		button = editBtn->getOrAddComponent<Button>();
		button->setText("Edit");
		editBtn->getOrAddComponent<ButtonScript>();
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

