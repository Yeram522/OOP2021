#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Position.h"
#include "Input.h"
#include "Score.h"
#include "Block.h"
#include "Panel.h"
#include "TetrisGame.h"

using namespace std;

// https://github.com/beomjoo90/OOP2021 , branch: 2학기

int main()
{
	//Position p1{ 1,2 };
	//Position p2{ 2,3 };

	////p1 += p2; // p1 will be {3,5}

	//auto p3 = 3 * (p1 + p2) - p2 * 2;  // p3 will be {11,18}

	//cout <<"p1" << p1 << endl;
	//cout << "p3" <<p3 << endl;
	

	//game
	auto screen = Screen::GetInstance();
	auto input = Input::GetInstance();
	auto tetris = new TetrisGame;

	tetris->loadData();

	while (tetris->isGameOver() == false) 
	{
		screen->clear();
		input->readInputs();

		tetris->internalUpdate();
		tetris->updatePos(false); // the location of the root game object won't be changed.
		tetris->internalDraw();

		screen->render();

		Sleep(100);
	}

	delete tetris;

	return 0;
}
