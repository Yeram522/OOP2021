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
	GameObject* player;//�︮����
	GameObject* board; //Game State UI

	string sprite = "\xCD\xCD\xCB\xCD\xCD\xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0";
	MoveMapScript* mapScript;
	Animator* animator;

	Renderer* mapRender;
	
public:
	HelicopterGame(int scenenumber):Scene(scenenumber), player(nullptr)
	{
		//�ǳ� �̿�� �ٿ���� �и� ���� ������ �ϴ��� �ּ�ó����.
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
		animator = player->getOrAddComponent<Animator>();//�ִϸ����� �߰� �� ��������
		animator->addClip({ "\xCD\xCD\xCB\xCD\xCD\xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4} });
		animator->addClip({ "  \xCB  \xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4} });//Ŭ���߰�.
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

		ifstream fin("mapdata.txt");//�Է½�Ʈ���� �����ϱ� ���� ��ü�� ���� �� ���� ����

		if (fin.fail()) {
			Borland::gotoxy(10, 40);
			cout << "���� ���¿� �����߽��ϴ�." << endl;
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

    void moveMap()//�������� ���� �̵��Ѵ�.
	{

		string mapdata = "";//���� ���� �̹��� ��������.
		mapdata.append(mapRender->getShape());

		for (int i = 0; i < mapRender->getDimension().y; i++)
		{
			int index = i * mapRender->getDimension().x;
			string temp;//�ڷ� push�� char
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

