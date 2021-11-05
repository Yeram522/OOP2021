#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Position.h"
#include "Input.h"
#include "TetrisMapMaker.h"

using namespace std;

// https://github.com/beomjoo90/OOP2021 , branch: 2학기

int main()
{
	auto screen = Screen::GetInstance();
	auto input = Input::GetInstance();
	auto mapmaker = new TetrisMapMaker;

	while (mapmaker->isGameOver() == false) 
	{
		screen->clear();
		input->readInputs();

		mapmaker->internalUpdate();
		mapmaker->updatePos(false); // the location of the root game object won't be changed.
		mapmaker->internalDraw();

		screen->render();

		Sleep(100);
	}

	delete mapmaker;

	return 0;
}
