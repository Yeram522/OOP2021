#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <Utils.h>
#include <iostream>
#include <conio.h> // console io
#include <cstring> // string.h
#include <cstdlib> // stdlib.h
#include <string> // c++ string class
#include <Windows.h>



// https://github.com/beomjoo90/OOP2021 , 수업 끝나구 branch: 2학기 브랜치 다운받기!!

const int directionToLeft = 0;
const int directionToRight = 1;

class Screen;
class Player;



class Screen {
private:
	int		width; //visible width
	// width +1 : // region with visible width and invisible line
	int		height;
	int     size;
	char*	canvas;

public:

	// constructor (생성자 함수) 메모리공간상에 적재되는 순간 호출되는
	Screen(unsigned int width, unsigned int height)
		:width(width), height(height), canvas( new char[(width+1)*height])
	{
		bool faultyInput = false;
		if (this->width == 0) {
			this->width = 10;
			faultyInput = true;
		}
		if (this->height == 0) {
			this->height = 10 ;
			faultyInput = true;
		}
		if (faultyInput == true) {
			delete canvas;
			canvas = new char[(this->width + 1) * this->height];
		}
		size = (this->width + 1) * this->height;
	}

	// destructor (소멸자 함수) 메모리공간상에서 없어지는 순간 호출되는 함수
	//상속받은 객체를 업캐스팅해서 딜리트할 때 그 객체의 소멸자를 호출해야 하기 떄문!
	virtual ~Screen()
	{
		delete[] canvas;
		canvas = nullptr;
		width = 0; height = 0;
	}

	void clear()
	{
		memset(canvas, ' ', size);
		for (int h = 0; h < height; h++)
			canvas[(width+1) * (h+1)-1] = '\n'; //이거 왜 그런지 계산.식 왜그런지
		canvas[size - 1] = '\0';
	}

	//원하는 위체에 원하는 사이즈로 draw
	void draw(const Position pos, const char* shape, const Dimension sz)
	{
		int offset = (width + 1) * pos.y + pos.x;

		for (int h = 0; h < sz.y; h++)		
			strncpy(&canvas[offset + (width + 1) * h], &shape[h * (sz.x + 1), sz.x]);
		
	}

	void render()
	{
		for(int h =0;h<height;h++)
	}
};
class GameObject
{
private:
	char	face[20];
	int		pos;
	int		direction;
	Screen* screen;
	GameObject** gameObjects;

public:

	GameObject(GameObject** gameObjects, Screen* screen, const char* face, int pos, int direction) 
		: pos(pos), direction(direction), screen(screen), gameObjects(gameObjects)
	{
		setFace(face);
	}
	virtual ~GameObject() {}

	void move(int direction)
	{
		direction == directionToRight ? pos++: pos--;
	}
	void move()
	{
		(direction == directionToLeft) ? --pos : ++pos;
	}
	virtual void draw()
	{
		screen->draw(pos, face);
	}
	virtual void update() {}

	int getPos() { return pos; } // getter function
	void setPos(int pos) { this->pos = pos; } // setter function

	int getDirection() { return direction;  }
	void setDirection(int direction) { this->direction = direction; }

	const char* getFace() { return face;  }
	void setFace(const char* face) { strcpy(this->face, face); }

	Screen* getScreen() { return screen; }
	GameObject** getGameObjects() { return gameObjects; }
};



int main()
{	
	int major;
	int minor;

	Screen  screen(3,3);
	Position pos{ 0, 1 };
	Dimension sz{ 2,2 };

	
	// game loop

	bool isLooping = true;
	while (isLooping) {
		screen.clear();		  		


		screen.render();
		Sleep(100);

		
	}
	printf("\nGame Over\n");

	return 0;
}