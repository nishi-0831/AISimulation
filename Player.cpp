#include "Player.h"
#include "Input.h"
#include <algorithm>

namespace
{
	int keyArray[4] = { KEY_INPUT_W ,KEY_INPUT_S,KEY_INPUT_A ,KEY_INPUT_D };
}
Player::Player()
	:GameObject2D(),tile_({2,2})
{
	pos_ = Point({ 2 * CHA_SIZE,2 * CHA_SIZE });
	move = Point({ 0,0 });
}

Player::~Player()
{
}

void Player::Update()
{
	//moveDirArray
	SetDir();
	Move();
	/*for (int i = 0;i < 4;i++)
	{
		if (Input::IsKeyDown(keyArray[i]))
		{
			move = Add(move, moveDirArray[i]);
		}
	}*/

	//Point tileCopy = tile_;
	//tileCopy.x += move.x;
	//tileCopy.y += move.y;
	////ŠO˜g‚È‚ç‚à‚¤ˆê‰ñ
	//if (tileCopy.x == 0 || tileCopy.x == STAGE_WIDTH - 1 || tileCopy.y == 0 || tileCopy.y == STAGE_HEIGHT - 1)
	//{
	//	move = Point({ 0,0 });
	//}
	//tile_ = Add(tile_, move);
	//
	//pos_.x = tile_.x * CHA_SIZE;
	//pos_.y = tile_.y * CHA_SIZE;
}

void Player::SetDir()
{
	move = Point({ 0,0 });
	for (int i = 0;i < 4;i++)
	{
		if (Input::IsKeyDown(keyArray[i]))
		{
			move = Add(move, moveDirArray[i]);
		}
	}
}

void Player::Move()
{
	Point tileCopy = tile_;
	tileCopy.x += move.x;
	tileCopy.y += move.y;
	//ŠO˜g‚È‚ç‚à‚¤ˆê‰ñ
	if (tileCopy.x == 0 || tileCopy.x == STAGE_WIDTH - 1 || tileCopy.y == 0 || tileCopy.y == STAGE_HEIGHT - 1)
	{
		move = Point({ 0,0 });
	}
	tile_ = Add(tile_, move);

	pos_.x = tile_.x * CHA_SIZE;
	pos_.y = tile_.y * CHA_SIZE;
}

void Player::Draw()
{
	DrawBox(pos_.x , pos_.y , pos_.x + CHA_SIZE,pos_.y+CHA_SIZE, GetColor(0, 255, 0), true);
}
