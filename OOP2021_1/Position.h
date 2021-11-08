#pragma once
#include <ostream>;
using namespace std;


struct Position
{
	int x;
	int y;

	Position(int x = 0, int y = 0) : x(x), y(y) {}
	Position(const Position& other) : Position(other.x, other.y) {} // copy constructor

	Position operator+(const Position& other)
	{
		x = x + other.x;
		y = y + other.y;

		return Position(x, y);
	}
	Position operator-(const Position& other)
	{
		x = x - other.x;
		y = y - other.y;

		return Position(x, y);
	}

	Position operator*(const Position& other)
	{
		x = x * other.x;
		y = y * other.y;

		return Position(x, y);
	}

	Position& operator+=(const Position& other)
	{
		this->x = this->x + other.x;
		this->y = this->y + other.y;

		return *this;
	}

	Position& operator=(const Position& other)
	{
		this->x = other.x;
		this->y = other.y;

		return *this;
	}

	Position& operator()(const Position& pos)
	{

		return *this;
	}

	friend ostream& operator<<(ostream& cout, const Position& pos)
	{
		cout << '[' << pos.x << ',' << pos.y << ']' << endl;

		return cout;
	}


	//교환 법칙 성립하게 구현
	friend Position operator*(const int n, Position& other)
	{
		other.x = n * other.x;
		other.y = n * other.y;

		return other;
	}

	friend Position operator*(Position& other, int n)
	{
		other.x = n * other.x;
		other.y = n * other.y;

		return other;
	}

	static Position up;
	static Position right;
	static Position down;
	static Position left;
	static Position zeros;
	static Position ones;

};

typedef Position Dimension;








