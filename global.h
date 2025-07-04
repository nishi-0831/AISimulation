#pragma once
#include <cmath>



	//�񎟌��x�N�g��(����)
	struct Point
	{
		int x;
		int y;
		//a��b�𑫂���
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
		//a����b��������
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
			//2�_ (x1, y1) �� (x2, y2) �Ԃ̃}���n�b�^�������́A
			// |x1 - x2| + |y1 - y2| �Ōv�Z����܂�
			return abs(a.x - b.x) + abs(a.y - b.y);
		}

	};
	
	//�񎟌��x�N�g��(���������_��)
	struct Pointf
	{
		float x;
		float y;
	};

	//��`(������)��\����
	struct Rect
	{
		int x;//����x
		int y;//����y
		int w;//��
		int h;//����
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



	const int CHA_SIZE = 32;//�L�����N�^�[�̃T�C�Y

	const int STAGE_WIDTH = 39;
	const int STAGE_HEIGHT = 21;
