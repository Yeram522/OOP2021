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
#include "Collider.h"
#include "Button.h"
#include "boardScript.h"


using namespace std;



class HelicopterGame: public Scene
{
	GameObject* map;
	GameObject* player;//헬리콥터
	GameObject* board; //Game State UI

	string sprite = "\xCD\xCD\xCB\xCD\xCD\xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0";
	MoveMapScript* mapScript;
	Animator* animator;

	Renderer* mapRender;
	
public:
	HelicopterGame(int scenenumber):Scene(scenenumber), player(nullptr)
	{
		//판낼 이용시 바운더리 밀림 현상 때문에 일단은 주석처리함.
		/*GameObject* screenUI = new GameObject("mapframe", "ui", nullptr, { 50,20 }, { 5,5 }, Position::zeros, nullptr);
		auto panelScript = screenUI->getOrAddComponent<PanelScript>();
		panelScript->setTitle(" screen");
		rootChildren.push_back(screenUI);*/
		
		map = new GameObject("map", "panel", nullptr, { 50,20 }, { 5,5 }, Position::zeros, nullptr);
		rootChildren.push_back(map);

		mapScript = map->getOrAddComponent<MoveMapScript>();

		mapRender = map->getComponent<Renderer>();
		mapScript->movemapLeft = [&]() {moveMap(); };
	
		int size = mapRender->getDimension().x * mapRender->getDimension().y;
		mapRender->setShape(loadData(size));

		player = new GameObject{ "helicopter", "player", sprite.c_str(),
			{5,4}, {0,10},  Position::zeros, map };
		player->addComponent<RigidBody>();
		player->addComponent<Collider>();
		animator = player->getOrAddComponent<Animator>();//애니메이터 추가 및 가져오기
		animator->addClip({ "\xCD\xCD\xCB\xCD\xCD\xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4} });
		animator->addClip({ "  \xCB  \xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4} });//클립추가.
		player->addComponent<PlayerMoveScript>();

		board = new GameObject("board", "ui", nullptr, { 10,3 }, { 25,27}, Position::zeros, nullptr);
		auto button = board->getOrAddComponent<Button>();
		button->setText("Time: 0s");
		board->addComponent<boardScript>();
		rootChildren.push_back(board);
		

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

		
		return result;

	}

    void moveMap()//좌측으로 맵을 이동한다.
	{

		string mapdata = "";//현재 맵의 이미지 가져오기.
		mapdata.append(mapRender->getShape());

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

	bool isGameOver()
	{
		if (player->getComponent<PlayerMoveScript>()->getIsCrushed())
		{
			board->getComponent<boardScript>()->stopTimer();
			board->getComponent<Button>()->setText("GameOver");		
			return true;
		}
		return false;
	}

	void start() override
	{
		board->getComponent<boardScript>()->startTimer();
	}

	void update() override {
		if (isGameOver())
		{
			map->setFreeze();
			player->setFreeze();
		}
		animator->Play();
		
		Scene::update();
	}
};

