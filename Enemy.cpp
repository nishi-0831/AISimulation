#include "Enemy.h"
#include "DxLib.h"
#include <assert.h>
#include "Input.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "time.h"
#include "global.h"
#include "Player.h"
#include "RouteSearch.h"
#include <vector>

#define test 1
namespace
{
	static float chaseTime = 0;
	static float timer = 0;
	float moveInterval = 0.1f;
	const int THRESHOLD_DIST = 30;
	Player* p;
	std::vector<Point> route;

	Point mark;
}
void Enemy::UpdateNormal()
{
	SetDir();
	Move();
	//�v���C���[�Ƃ̃}���n�b�^��������THRESHOLD_DIST��菬�����Ȃ�����
	int manhattanDistance = Point::ManhattanDistance(tile_, p->GetTilePos());
	if (manhattanDistance < THRESHOLD_DIST)
	{
		state_ = ESTATE::CHASE;
	}
}
void Enemy::UpdateChase()
{
	//10�b�ȓ��ɒǂ����Ȃ�������NORMAL�ɖ߂�
	chaseTime += Time::DeltaTime();
	if (chaseTime >= 10)
	{
		state_ = ESTATE::NORMAL;
	}
#if test
	routeSearch->SetStartTile(tile_);
	routeSearch->SetEndTile(p->GetTilePos());
	//route =routeSearch->CalculateRoute();

	mark = routeSearch->CalculateRoute();
	tile_ = mark;
#endif
}
void Enemy::UpdateEscape()
{
}
Enemy::Enemy()
	:GameObject2D(),tile_({4,4}),  hImage_{-1}
{
	routeSearch = new RouteSearch();
	p = (Player*)FindGameObject<Player>();
	imageSize_ = 48;
	dirArray_ = { 3,0,1,2,0 };
	animTip_ = { 0,1,2,1 }; // �A�j���[�V�����̃R�}�ԍ�
	animTimer_ = 0;
	hImage_ = LoadGraph("Assets/mogu.png");
	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����


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


}

void Enemy::Move()
{
	bool flag = false;
#if 1
	while (!flag)
	{
		Point tileCopy = tile_;
		tileCopy.x += moveDirArray[nowDir_].x;
		tileCopy.y += moveDirArray[nowDir_].y;
		//�O�g�Ȃ�������
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
#endif

#if test
	
#endif
	
	pos_.x = tile_.x * CHA_SIZE;
	pos_.y = tile_.y * CHA_SIZE;
}

void Enemy::Update()
{
	Anim();
	timer += Time::DeltaTime();
	//mark = tile_;
#if 1
	if (timer >= moveInterval)
	{
		switch (state_)
		{
		case ESTATE::NORMAL:
			UpdateNormal();
			break;
		case ESTATE::CHASE:
			UpdateChase();
			break;
		case ESTATE::ESCAPE:
			UpdateEscape();
			break;
		default:
			return;
		}
		timer = timer - moveInterval;
	}
#else
	if (timer >= moveInterval)
	{
		SetDir();
		Move();
		timer = timer - moveInterval;
	}
#endif
	
	
}

void Enemy::Draw()
{
	//�c48 ,��48
	Rect rect{ pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE };
	DrawRectExtendGraph(pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE, animTip_[nowFrame_] * imageSize_, dirArray_[nowDir_] * imageSize_, imageSize_, imageSize_, hImage_, TRUE);
}
