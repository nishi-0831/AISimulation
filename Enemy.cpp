#include "Enemy.h"
#include "DxLib.h"
#include <assert.h>
#include "Input.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "time.h"
#include "global.h"

namespace
{
	static float timer = 0;
	float moveInterval = 0.1f;

	//const int IMAGE_SIZE = 48;
	//int nowFrame_ = 0;
	
	//int animFrame_[4]{ 0,1,2,1 };
	//float animInterval = 0.3f;
	/*
	int keyArray[4] = { KEY_INPUT_W ,KEY_INPUT_S,KEY_INPUT_A ,KEY_INPUT_D };
	Point moveDirArray[(int)DIR::MAX_DIR] = {
		{0,-1},
		{0,1},
		{-1,0},
		{1,0},
		{0,0}
	};
	DIR nowDir = DIR::LEFT;*/
}
Enemy::Enemy()
	:GameObject2D(),tile_({4,4}),  hImage_{-1}
{
	imageSize_ = 48;
	dirArray_ = { 3,0,1,2,0 };
	animTip_ = { 0,1,2,1 }; // アニメーションのコマ番号
	animTimer_ = 0;
	hImage_ = LoadGraph("Assets/mogu.png");
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化


	//tile_.x = GetRand(STAGE_WIDTH - 1)-1;
	//tile_.y = GetRand(STAGE_HEIGHT - 1)-1;
	//STAGE_WIDTHで割ったら
	//0から38
	//+1して1から39
	//STAGE_WIDTH-1(38)で割ったら0~37 1足せば1から38

	tile_.x = GetRand(RAND_MAX) % (STAGE_WIDTH-1) + 1;
	tile_.y = GetRand(RAND_MAX) % (STAGE_HEIGHT-1) + 1;

	pos_ = Point({ tile_.x * CHA_SIZE,tile_.y * CHA_SIZE });

	nowDir_ = DIR::LEFT;
	
	assert(hImage_ > 0);
}

Enemy::~Enemy()
{
}

void Enemy::SetDir()
{
	//nowDir_ = (DIR)(rand() % (int)DIR::MAX_DIR);
	//TurnLeft();
}



void Enemy::Anim()
{
	animTimer_ += Time::DeltaTime();
	if (animTimer_ >= animInterval_)
	{
		index_ = index_ % 4;
		nowFrame_ = animTip_[index_];
		animTimer_ -= animInterval_;
		index_++;
	}

#if 0
	timer += Time::DeltaTime();


	if (timer >= moveInterval)
	{
		SetDir();
		Move();
		timer = timer - moveInterval;
	}
# endif
}

void Enemy::Move()
{
	bool flag = false;
	while (!flag)
	{
		Point tileCopy = tile_;
		tileCopy.x += moveDirArray[nowDir_].x;
		tileCopy.y += moveDirArray[nowDir_].y;
		//外枠ならもう一回
		if (IsOutOfStage(tileCopy.x, tileCopy.y))
		{
			flag = false;
			//SetDir();
			TurnLeft();
		}
		else
		{
			tile_ = tileCopy;
			flag = true;
		}
	}

	pos_.x = tile_.x * CHA_SIZE;
	pos_.y = tile_.y * CHA_SIZE;
}

void Enemy::Update()
{
	Anim();
	timer += Time::DeltaTime();

	if (timer >= moveInterval)
	{
		SetDir();
		Move();
		timer = timer -moveInterval;
	}

	
}

void Enemy::Draw()
{
	//縦48 ,横48
	Rect rect{ pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE };
	DrawRectExtendGraph(pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE, animTip_[nowFrame_] * imageSize_, dirArray_[nowDir_] * imageSize_, imageSize_, imageSize_, hImage_, TRUE);
}
