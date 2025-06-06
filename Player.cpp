#include "Player.h"
#include "Input.h"
#include <algorithm>
#include "ImGuiSample.h"

namespace
{
	int keyArray[4] = { KEY_INPUT_W ,KEY_INPUT_S,KEY_INPUT_A ,KEY_INPUT_D };
	const int IMAGE_SIZE = 48;
	const DIR PLAYER_INIT_DIR = { DOWN };
	//static int nowFrame_ = 0;
	//int animFrame_[4]{ 0,1,2,1 };//アニメーションのコマ番号
	float moveInterval = 1.0f;//アニメーションの一コマのインターバル

	float animInterval = 0.3f;
}
Player::Player()
	:GameObject2D(), tile_({ 2,2 })
{
	imageSize_ = 48;
	dirArray_ = { 3,0,1,2,0 };
	animTip_ = { 0,1,2,1 }; // アニメーションのコマ番号
	hImage_ = LoadGraph("Assets/mogu.png");
	pos_ = Point({ tile_.x * CHA_SIZE,tile_.y * CHA_SIZE });
	move = moveDirArray[DIR::NONE];
	
}

Player::~Player()
{
}

void Player::Update()
{
	//moveDirArray
	SetDir();
	Move();

	static float animTimer = animInterval;
	animTimer += Time::DeltaTime();
	static int frame = 0;

	//nowFrame = animFrame[frame];
	if (animTimer >= animInterval)
	{
		frame = frame % 4;
		nowFrame_ = animTip_[frame];
		animTimer -= animInterval;
		frame++;
	}
}

void Player::SetDir()
{
	move = Point({ 0,0 });
	for (int i = 0;i < 4;i++)
	{
		if (Input::IsKeyDown(keyArray[i]))
		{
			move = Point::Add(move, moveDirArray[i]);
			nowDir_ = (DIR)i;
		}
		//何もしないとき、押してないときの処理も入れたほういい
	}
	
}

void Player::Move()
{
	Point tileCopy = tile_;
	tileCopy.x += move.x;
	tileCopy.y += move.y;
	//外枠ならもう一回

	if (tileCopy.x == 0 || tileCopy.x == STAGE_WIDTH - 1 || tileCopy.y == 0 || tileCopy.y == STAGE_HEIGHT - 1)
	{
		move = Point({ 0,0 });
	}
	tile_ = Point::Add(tile_, move);

	pos_.x = tile_.x * CHA_SIZE;
	pos_.y = tile_.y * CHA_SIZE;
}

void Player::Draw()
{
	//縦48 ,横48
	Rect rect{ pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE };
	//DrawBox(pos_.x , pos_.y , pos_.x + CHA_SIZE,pos_.y+CHA_SIZE, GetColor(0, 255, 0), true);
	DrawRectExtendGraph(pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE, animTip_[nowFrame_] * IMAGE_SIZE, dirArray_[nowDir_] * IMAGE_SIZE, IMAGE_SIZE, IMAGE_SIZE, hImage_, TRUE);
}
