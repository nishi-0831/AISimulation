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
#include "State.h"
#define test 1
namespace
{
	static float chaseTime = 0;
	static float timer = 0;
	float moveInterval = 1.0f;
	const int THRESHOLD_DIST = 30;
	Player* p;
	std::vector<Point> route;
	ImGuiSample imguiSample;
	Point mark;
}


void Enemy::Update()
{
	Anim();
	
	switch (updateState_)
	{
		case UPDATESTATE::AUTO:
			timer += Time::DeltaTime();
			if (timer >= moveInterval)
			{
				isUpdateCommandReceived_ = true;
				timer = timer - moveInterval;
			}
			break;
		case UPDATESTATE::DEBUG:
			if (imguiSample.IsButtonDown())
			{
				isUpdateCommandReceived_ = true;
			}
			break;
	}
	if (isUpdateCommandReceived_)
	{
		//stateFunc_.at(currentEstate_)();
		Move();
		isUpdateCommandReceived_ = false;
	}
	for (auto s : eState_)
	{
		if ((*s).ID() == currentEstate_)
		{
			//s->func_();
			imguiSample.Log("state:" + s->name_);
			break;
		}
	}

	//違う
	if (imguiSample.IsButtonDown())
	{
		if (updateState_ == UPDATESTATE::AUTO)
		{
			updateState_ = UPDATESTATE::DEBUG;
		}
		else
		{
			updateState_ = UPDATESTATE::AUTO;
		}
	}

}

Enemy::Enemy()
	:GameObject2D(),tile_({4,4}),  hImage_{-1}
{
	routeSearch = new RouteSearch();
	p = (Player*)FindGameObject<Player>();
	imageSize_ = 48;
	dirArray_ = { 3,0,1,2,0 };
	animTip_ = { 0,1,2,1 }; // アニメーションのコマ番号
	animTimer_ = 0;
	hImage_ = LoadGraph("Assets/mogu.png");
	isUpdateCommandReceived_ = false;
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化


	tile_.x = GetRand(RAND_MAX) % (STAGE_WIDTH-1) + 1;
	tile_.y = GetRand(RAND_MAX) % (STAGE_HEIGHT-1) + 1;

	pos_ = Point({ tile_.x * CHA_SIZE,tile_.y * CHA_SIZE });

	nowDir_ = DIR::LEFT;
	
    

	eState_.push_back(new State("Normal", ESTATE::NORMAL, [this]() {this->UpdateNormal(); }));
	eState_.push_back(new State("Chase", ESTATE::CHASE, [this]() {this->UpdateChase(); }));
	eState_.push_back(new State("Escape", ESTATE::ESCAPE, [this]() {this->UpdateEscape(); }));

    //imguiSample.AddSelect()

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
	for (auto s : eState_)
	{
		if ((*s).ID() == currentEstate_)
		{
			s->func_();
			imguiSample.Log("state:" + s->name_);
			break;
		}
	}
	pos_.x = tile_.x * CHA_SIZE;
	pos_.y = tile_.y * CHA_SIZE;
}



void Enemy::Draw()
{
	//縦48 ,横48
	Rect rect{ pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE };
	DrawRectExtendGraph(pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE, animTip_[nowFrame_] * imageSize_, dirArray_[nowDir_] * imageSize_, imageSize_, imageSize_, hImage_, TRUE);
	imguiSample.Draw();
}
void Enemy::UpdateNormal()
{
	//imguiSample.Log("UpdateNormal");
	SetDir();
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

	//プレイヤーとのマンハッタン距離がTHRESHOLD_DISTより小さくなったら
	int manhattanDistance = Point::ManhattanDistance(tile_, p->GetTilePos());
	if (manhattanDistance < THRESHOLD_DIST)
	{
		currentEstate_ = ESTATE::CHASE;
	}
}
void Enemy::UpdateChase()
{
	chaseTime += Time::DeltaTime();
	if (chaseTime >= 10)
	{
		currentEstate_ = ESTATE::NORMAL;
		chaseTime = 0;
	}
#if test
	routeSearch->SetStartTile(tile_);
	routeSearch->SetEndTile(p->GetTilePos());

	mark = routeSearch->CalculateRoute();
	imguiSample.AddParameter("mark:" + std::to_string(mark.x) + "," + std::to_string(mark.y));
	tile_ = mark;
#endif
}
void Enemy::UpdateEscape()
{
	//imguiSample.Log("UpdateChase");
}