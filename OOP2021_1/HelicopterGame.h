#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include "Scene.h"
#include "PanelScript.h"
#include "MapEditor.h"
#include "MoveMapScript.h"
#include "PlayerMoveScript.h"
#include "Animator.h"
#include "RigidBody.h"

using namespace std;



class HelicopterGame: public Scene
{
	GameObject* map;
	GameObject* player;//헬리콥터
	string sprite = "\xCD\xCD\xCB\xCD\xCD\xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0";
	MoveMapScript* mapScript;
	Animator* animator;

	Renderer* mapRender;

	vector<GameObject*> rootChildren;
public:
	HelicopterGame(int scenenumber):Scene(scenenumber), player(nullptr)
	{
		
		map = new GameObject("map", "panel", nullptr, { 50,20 }, { 5,5 }, Position::zeros, nullptr);
		rootChildren.push_back(map);

		//판낼 이용시 바운더리 밀림 현상 때문에 일단은 주석처리함.
		//auto panelScript = map->getOrAddComponent<PanelScript>();
		//panelScript->setTitle(" screen");

		mapScript = map->getOrAddComponent<MoveMapScript>();

		mapRender = map->getComponent<Renderer>();
		mapScript->movemapLeft = [&]() {moveMap(); };
	
		int size = mapRender->getDimension().x * mapRender->getDimension().y;
		mapRender->setShape(loadData(size));

		player = new GameObject{ "helicopter", "player", sprite.c_str(),
			{5,4}, {0,10},  Position::zeros, map };
		player->addComponent<PlayerMoveScript>();
		player->addComponent<RigidBody>();
		animator = player->getOrAddComponent<Animator>();//애니메이터 추가 및 가져오기
		animator->addClip({ "\xCD\xCD\xCB\xCD\xCD\xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4} });
		animator->addClip({ "  \xCB  \xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4} });//클립추가.

	};

	char* loadData(int mapsize)
	{
		char* result = new char[mapsize];

		ifstream fin("mapdata.txt");//입력스트림을 관리하기 위한 객체를 선언 및 파일 열기

		if (fin.fail()) {
			Borland::gotoxy(10, 40);
			cout << "파일 오픈에 실패했습니다." << endl;
			return nullptr;
		}

		fin >> result;


		for (int i = 0; i < mapsize; i++)
		{
			if (result[i] == '0') result[i] = ' ';
			else if (result[i] == '1') result[i] = '\xB0';
			else if (result[i] == '2') result[i] = '\xB2';
			else if (result[i] == '3') result[i] = '\xDB';
		}

		Borland::gotoxy(10, 40); printf("loadBtn button %d\n");
		return result;

	}

    void moveMap()//좌측으로 맵을 이동한다.
	{
		//Borland::gotoxy(10, 41); printf("move Map!!%d\n", mapRender->getDimension().y);
		string mapdata = "";//현재 맵의 이미지 가져오기.
		mapdata.append(mapRender->getShape());
		Borland::gotoxy(10, 42); printf("player Position!!%d, %d\n", player->getTransform()->getPos().x, player->getTransform()->getPos().y);
		
		for (int i = 0; i < mapRender->getDimension().y; i++)
		{
			int index = i * mapRender->getDimension().x;
			string temp;//뒤로 push할 char
			temp.push_back(mapdata[index]);
			mapdata.erase(index, 1);
			mapdata.insert(index + mapRender->getDimension().x- 1, temp);
		}

		char* result = (char* )mapdata.c_str();
		mapRender->setShape(result);
	}



	void update() override {
		animator->Play();
		for (auto child : rootChildren) child->internalUpdate();
		rootChildren.erase(
			std::remove_if(rootChildren.begin(), rootChildren.end(),
				[](auto child) { return child->isActive() == false; }),
			rootChildren.end());
		for (auto child : rootChildren) child->internalRemove();
		for (auto child : rootChildren) child->internalRender();
	}
};

