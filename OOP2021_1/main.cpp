#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<iostream>
#include "Position.h"
#include "Input.h"
#if 0
#include "Score.h"
#include "Block.h"
#include "Panel.h"
#endif
#include "TetrisGame.h"
#include "SceneManager.h"
#include "MainScene.h"

using namespace std;


int main()
{
	
	auto screen = Screen::GetInstance();
	auto input = Input::GetInstance();
	auto sceneManager = SceneManager::GetInstance();
	auto main = new MainScene(sceneManager->getSceneCount());
	auto tetris = new TetrisGame(sceneManager->getSceneCount());
	
	sceneManager->createScene(main);
	sceneManager->createScene(tetris);

	sceneManager->enableScene((Scene*)main);
	while (tetris->isGameOver() == false) 
	{
		screen->clear();

		input->readInputs();

		sceneManager->loadScene();

		screen->render();

		Sleep(100);
	}

	delete tetris;

	return 0;
}
