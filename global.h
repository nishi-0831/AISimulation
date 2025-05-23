#pragma once

namespace
{


	//�񎟌��x�N�g��(����)
	struct Point
	{
		int x;
		int y;
	};

	inline Point Add(Point a, Point b)
	{
		a.x += b.x;
		a.y += b.y;
		return a;
	}

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
}