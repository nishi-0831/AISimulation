#pragma once
#include <cmath>



	//二次元ベクトル(整数)
	struct Point
	{
		int x;
		int y;
		//aとbを足すよ
		Point operator+(const Point& rhs)
		{
			return Point{ x + rhs.x, y + rhs.y };
		}
		Point operator-(const Point& rhs)
		{
			return Point{ x - rhs.x, y - rhs.y };
		}
		Point operator*(const int rhs)
		{
			return Point{ x * rhs, y * rhs };
		}
		Point operator/(const int rhs)
		{
			return Point{ x / rhs, y / rhs };
		}
		static Point Add(Point a, Point b)
		{
			a.x += b.x;
			a.y += b.y;
			return a;
		}
		//aからbを引くよ
		static Point Sub(Point a, Point b)
		{
			a.x -= b.x;
			a.y -= b.y;
			return a;
		}
		static Point Abs(Point point)
		{
			return Point{ abs(point.x),abs(point.y) };
		}
		static int ManhattanDistance(Point a, Point b)
		{
			//2点 (x1, y1) と (x2, y2) 間のマンハッタン距離は、
			// |x1 - x2| + |y1 - y2| で計算されます
			return abs(a.x - b.x) + abs(a.y - b.y);
		}

	};
	
	//二次元ベクトル(浮動小数点数)
	struct Pointf
	{
		float x;
		float y;
	};

	//矩形(くけい)を表すよ
	struct Rect
	{
		int x;//左上x
		int y;//左上y
		int w;//幅
		int h;//高さ
	};

	enum DIR
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
		MAX_DIR
	};

	static const Point moveDirArray[(int)DIR::MAX_DIR] = {
			{0,-1},
			{0,1},
			{-1,0},
			{1,0},
			{0,0}
	};



	const int CHA_SIZE = 32;//キャラクターのサイズ

	const int STAGE_WIDTH = 39;
	const int STAGE_HEIGHT = 21;
