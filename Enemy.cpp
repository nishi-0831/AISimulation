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
	int dirArray[(int)DIR::MAX_DIR] = { 3,0,1,2,0 };
	int animFrame[4]{ 0,1,2,1 };
	const int IMAGE_SIZE = 48;
	int nowFrame = 0;
	static float timer = 0;
	float interval = 1.0f;
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
	pos_ =Point({ tile_.x * CHA_SIZE,tile_.y * CHA_SIZE });
	srand((unsigned int)time(NULL)); // åªç›éûçèÇÃèÓïÒÇ≈èâä˙âª
	hImage_ = LoadGraph("Assets/mogu.png");
	//hImage_ = LoadDivGraph()
	assert(hImage_ > 0);
}

Enemy::~Enemy()
{
}

void Enemy::SetDir()
{
	nowDir = (DIR)(rand() % (int)DIR::MAX_DIR);
}

void Enemy::Move()
{
	//bool flag = false;
	//while (!flag)
	//{
	//	Point tileCopy = tile_;
	//	tileCopy.x += moveDirArray[nowDir].x;
	//	tileCopy.y += moveDirArray[nowDir].y;
	//	//äOògÇ»ÇÁÇ‡Ç§àÍâÒ
	//	if (tileCopy.x == 0 || tileCopy.x == STAGE_WIDTH - 1 || tileCopy.y == 0 || tileCopy.y == STAGE_HEIGHT - 1)
	//	{
	//		flag = false;
	//		SetDir();
	//	}
	//	else
	//	{
	//		tile_ = tileCopy;
	//		flag = true;
	//	}
	//}

	//pos_.x = tile_.x * CHA_SIZE;
	//pos_.y = tile_.y * CHA_SIZE;
}

void Enemy::Update()
{
	static float animTimer = 0;
	
	float animInterval = 0.3f;
	static int i=0;
	animTimer += Time::DeltaTime();
	if (animTimer >= animInterval)
	{
		i = i % 4;
		nowFrame = animFrame[i];
		animTimer -= animInterval;
		i++;
	}

	
	timer += Time::DeltaTime();


	if (timer >= interval)
	{
		nowDir = (DIR)(rand() % (int)DIR::MAX_DIR);
		bool flag = false;
		while (!flag)
		{
			Point tileCopy = tile_;
			tileCopy.x += moveDirArray[nowDir].x;
			tileCopy.y += moveDirArray[nowDir].y;
			//äOògÇ»ÇÁÇ‡Ç§àÍâÒ
			if (tileCopy.x == 0 || tileCopy.x == STAGE_WIDTH - 1 || tileCopy.y == 0 || tileCopy.y == STAGE_HEIGHT - 1)
			{
				flag = false;
				nowDir = (DIR)(rand() % (int)DIR::MAX_DIR);
			}
			else
			{
				tile_ = tileCopy;
				flag = true;
			}
		}
		
		pos_.x = tile_.x * CHA_SIZE;
		pos_.y = tile_.y * CHA_SIZE;
		
		timer = timer -interval;
	}

	
}

void Enemy::Draw()
{
	//èc48 ,â°48
	Rect rect{ pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE };
	DrawRectExtendGraph(pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE, animFrame[nowFrame] * IMAGE_SIZE, dirArray[nowDir] * IMAGE_SIZE, IMAGE_SIZE, IMAGE_SIZE, hImage_, TRUE);
}
