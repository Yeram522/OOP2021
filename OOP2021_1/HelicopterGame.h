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
	GameObject* player;//�︮����
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

		//�ǳ� �̿�� �ٿ���� �и� ���� ������ �ϴ��� �ּ�ó����.
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
		animator = player->getOrAddComponent<Animator>();//�ִϸ����� �߰� �� ��������
		animator->addClip({ "\xCD\xCD\xCB\xCD\xCD\xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4} });
		animator->addClip({ "  \xCB  \xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4} });//Ŭ���߰�.

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

		Borland::gotoxy(10, 40); printf("loadBtn button %d\n");
		return result;

	}

    void moveMap()//�������� ���� �̵��Ѵ�.
	{
		//Borland::gotoxy(10, 41); printf("move Map!!%d\n", mapRender->getDimension().y);
		string mapdata = "";//���� ���� �̹��� ��������.
		mapdata.append(mapRender->getShape());
		Borland::gotoxy(10, 42); printf("player Position!!%d, %d\n", player->getTransform()->getPos().x, player->getTransform()->getPos().y);
		
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

