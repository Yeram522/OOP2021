#pragma once
#include <iostream>
#include "Panel.h"

class Map : public Panel {
	bool*		map;
	int			upper;

	static const char rect = '\xdb';

public:
	Map(const Position& pos, int width, int height, GameObject* parent)
		: map(new bool[(size_t)width * height]), upper(height - 1),
		Panel("", pos, width, height, parent)
	{
		for (int i = 0; i < width * height; i++) 
			map[i] = false;
	}

	~Map() { if (map) delete[] map; }

	bool isDone() const { return upper <= 0; }

	//클릭했을때 이미 장애물이 설치되어있으면 true 반환
	bool isObstacleExist(Position pos) const {
		if (getShape(pos) == ' ') return false;
		return true;
	}

	//장애물이 설치되어있으면 장애물 삭제
	bool deleteObstacle(Position pos) {
		if (!isObstacleExist(screen2local(pos))) return false;	
		setShape(' ', screen2local(pos));
		return true;
	}

	bool isValidRange(const Position& mouspos)
	{
		if (this->local2Screen().x <= input->getMousePosition().x && input->getMousePosition().x <= this->local2Screen().x + this->getDimension().x
			&& this->local2Screen().y <= input->getMousePosition().y && input->getMousePosition().y <= this->local2Screen().y + this->getDimension().y)
			return true;

		return false;
	}

	//클릭한 장소에 장애물 설치
	void place(const Position& pos) { setShape(rect, screen2local(pos));}

	void draw()
	{
		Panel::draw();
		auto height = dim.y;
		auto width = dim.x;

		for (int i = upper+1; i < height; i++) {
			for (int j = 0; j < width; j++) {
				setShape(map[j + i * width] ? rect : ' ', j + i * width);
			}
		}
		GameObject::draw();
	}

};