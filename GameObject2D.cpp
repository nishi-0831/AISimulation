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
	nowDir = DIR::NONE;
	pos_ = Point({ tile_.x * CHA_SIZE,tile_.y * CHA_SIZE });
}

GameObject2D::~GameObject2D()
{
}

void GameObject2D::Update()
{
}

void GameObject2D::Draw()
{
}
