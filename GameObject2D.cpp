#include "GameObject2D.h"
#include <assert.h>

//namespace
//{
//	const int IMAGE_SIZE = 48;
//
//	int dirArray[(int)DIR::MAX_DIR] = { 3,0,1,2,0 };
//	int keyArray[4] = { KEY_INPUT_W ,KEY_INPUT_S,KEY_INPUT_A ,KEY_INPUT_D };
//	Point moveDirArray[(int)DIR::MAX_DIR] = {
//		{0,-1},
//		{0,1},
//		{-1,0},
//		{1,0},
//		{0,0}
//	};
//	DIR nowDir = DIR::LEFT;
//}

GameObject2D::GameObject2D()
	:GameObject(), tile_({ 4,4 }), hImage_{ -1}
{

	nowDir_ = DIR::NONE;
	pos_ = Point({ tile_.x * CHA_SIZE,tile_.y * CHA_SIZE });
}

GameObject2D::~GameObject2D()
{
}

void GameObject2D::TurnLeft()
{
	switch (nowDir_)
	{
	case DIR::UP:
	case DIR::NONE:
		nowDir_ = DIR::LEFT;
		break;
	case DIR::RIGHT:
		nowDir_ = DIR::UP;
		break;
	case DIR::DOWN:
		nowDir_ = DIR::RIGHT;
		break;
	case DIR::LEFT:
		nowDir_ = DIR::DOWN;
		break;
	
		
	}

}

void GameObject2D::TurnRight()
{
	switch (nowDir_)
	{
	case DIR::UP:
	case DIR::NONE:
		nowDir_ = DIR::RIGHT;
		break;
	case DIR::RIGHT:
		nowDir_ = DIR::DOWN;
		break;
	case DIR::DOWN:
		nowDir_ = DIR::LEFT;
		break;
	case DIR::LEFT:
		nowDir_ = DIR::UP;
		break;
	}
}

void GameObject2D::TurnBack()
{
	switch (nowDir_)
	{
	case DIR::UP:
	case DIR::NONE:
		nowDir_ = DIR::DOWN;
		break;
	case DIR::RIGHT:
		nowDir_ = DIR::LEFT;
		break;
	case DIR::DOWN:
		nowDir_ = DIR::UP;
		break;
	case DIR::LEFT:
		nowDir_ = DIR::RIGHT;
		break;
	}
}

bool GameObject2D::IsOutOfStage(int x, int y)
{
	bool rt = false;
	if (x == 0 || x >= STAGE_WIDTH -1 || y == 0 || y >= STAGE_HEIGHT -1)
	{
		rt = true;
	}
	return rt;
}

void GameObject2D::Update()
{
}

void GameObject2D::Draw()
{
}
