#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <Windows.h>

//Ŭ������ ����ü�� ������ �ٸ���.
struct Position {
	static int x;
	int _x;
	static int y; //static������ ����� ���Ǹ� ���ÿ� �� �� ����.
	int _y;
	Position(int x = 0, int y = 0) : _x(_x), _y(_y) {}//Default ���� �Ű������� �ִ�.

	static int count; //static���� ����Ǹ� ��������� �ƴϴ�.

	void print()
	{
		printf("(%d,%d)", this->x, this->y);
	}

	static void globalprint() //static �Լ��� ��üȭ ��Ű�� �ʰ� �̹� �����Ѵ�. Position::globalPrint();   static�� ���������� ���� ��Ȱ�� �Ѵ�. ���������� Ŭ���� �Ҽ��� ����.
	{
		printf("(%d,%d)", x, y); //this->x, this->y �� ���� ������ �Ұ���. this�� �𸣱� �����̴�.
	}
};

//Position myPos;
//Position myPos2(3); //myPos2.x ? �κ��� ����Ʈ�� ���� x=3, y=0


//instantiate: �޸𸮿� �����Ű�� ���� <- instantiate
//realization(��üȭ ��Ų��): <- realize
//materialize: ����ȭ ��Ų��. <- materialize
//reify(thingfy)

//�����ּ�= this

class Borland {

public: //Ŭ����->��üȭ->"����ȭ" :  Instantiation / �����Ҵ�: �޸𸮻� ����/ Ŭ����(���赵)�� ������Ʈ(����ȭ �Ǵ� ����) object instance/ instance ���δٸ� ������ �ִ���.
	static void initialize()
	{  //static���� ���ǵ� �Լ��� "����Լ�"��� ������ �ʴ´�. 
		//���: this��� �ϴ� ������ ������ ���� ����. static�� this��� ������ �𸥴�.
		CONSOLE_CURSOR_INFO cci;
		cci.dwSize = 25;
		cci.bVisible = FALSE;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	}

	static int wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.X;
	}
	static int wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.Y;
	}
	static void gotoxy(int x, int y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x, (SHORT)y });
	}
	static void gotoxy(const Position* pos)
	{
		if (!pos) return;
		gotoxy( (*pos).x, (*pos).y);
	}
	static void gotoxy(const Position& pos)
	{
		gotoxy( pos.x, pos.y);
	}
};

#endif 
