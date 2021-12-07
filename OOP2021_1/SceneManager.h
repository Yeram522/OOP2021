#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "TetrisGame.h"
#include "Scene.h"
using namespace std;

class Scene;

class SceneManager
{
	int scenecount;
	vector<Scene*> sceneinbuild;
	static SceneManager* Instance;
	Scene* CurrentScene;
	SceneManager():scenecount(0), CurrentScene(nullptr)
	{}
public:
	static SceneManager* GetInstance()
	{
		if (Instance == nullptr) {
			Instance = new SceneManager();
		}
		return Instance;
	}

	template <typename T>
	void createScene(T* newscene)
	{
		sceneinbuild.push_back((Scene*)newscene);
	}

	

	int getSceneCount() { return sceneinbuild.size(); };

	void enableScene(Scene* scene)
	{
		CurrentScene = scene;
		CurrentScene->setLoad(true);
		CurrentScene->update();
	}

	void enableSceneinIndex(int index)
	{
		disableScene(CurrentScene);
		for (auto scene : sceneinbuild)
			if (scene->getIndex() == index)
			{
				CurrentScene = scene;
				CurrentScene->setLoad(true);
				CurrentScene->update();
				return;
			}	
	}

	void disableScene(Scene* scene)
	{
		scene->setLoad(false);
		CurrentScene = nullptr;
	}

	void loadScene()
	{
		for (auto scene : sceneinbuild)
			if (scene->isLoaded()) scene->update();
	}


};

