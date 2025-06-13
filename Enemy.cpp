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
#include "ImGui/imgui.h"

#define test 1
namespace
{
	static float chaseTimer = 0;
	static float escapeTimer = 0;
	static float timer = 0;
	float moveInterval = 0.7f;
	float chaseInterval = 0.5f;
	float escapeInterval = 0.3f;
	const int THRESHOLD_DIST = 30;
	Player* p;
	std::vector<Point> route;
	const char* text;
}
void Enemy::UpdateNormal()
{
	SetDir();
	Move();
	//プレイヤーとのマンハッタン距離がTHRESHOLD_DISTより小さくなったら
	int manhattanDistance = Point::ManhattanDistance(tile_, p->GetTilePos());
	if (manhattanDistance < THRESHOLD_DIST)
	{
		state_ = ESTATE::CHASE;
	}
}
void Enemy::UpdateChase()
{
	
#if test
	routeSearch->SetStartTile(tile_);
	routeSearch->SetEndTile(p->GetTilePos());
	//route =routeSearch->CalculateRoute();

	Point movement = routeSearch->GetMovement();
	tile_ = Point::Add(tile_, movement);
	SetDir(movement);


#endif
}
void Enemy::UpdateEscape()
{
	
	//プレイヤーとのマンハッタン距離がTHRESHOLD_DISTより小さくなったら
	int manhattanDistance = Point::ManhattanDistance(tile_, p->GetTilePos());
	if (manhattanDistance < 10)
	{
		Point movement = routeSearch->GetMovement();
		tile_ = Point::Sub(tile_, movement);
		SetDir(Point{ -movement.x,-movement.y });
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
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化


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

void Enemy::SetDir(Point movement)
{
	for (int i = 0;i < (int)DIR::MAX_DIR; i++)
	{
		if (Point::Equal(movement, moveDirArray[i]))
		{
			nowDir_ = (DIR)i;
			return;
		}
	}
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
#endif


	
	
}

void Enemy::Update()
{
	Anim();
	timer += Time::DeltaTime();
	//mark = tile_;
#if 1
	
		switch (state_)
		{
		case ESTATE::NORMAL:
			if (timer >= moveInterval)
			{
				UpdateNormal();
				timer = 0.0f;
			}
			text = "NORMAL";
			break;
		case ESTATE::CHASE:
			text = "CHASE";
			// 10秒以内に追いつかなかったらNORMALに戻る
				chaseTimer += Time::DeltaTime();
			if (chaseTimer >= 4)
			{
				state_ = ESTATE::ESCAPE;
				chaseTimer = 0.0f;
			}
			if (timer >= chaseInterval)
			{
				UpdateChase();
				timer = 0.0f;
			}
			break;
		case ESTATE::ESCAPE:
			text = "ESCAPE";
			escapeTimer += Time::DeltaTime();
			if (escapeTimer >= 4)
			{
				state_ = ESTATE::NORMAL;
				escapeTimer = 0.0f;
			}
			if (timer >= escapeInterval)
			{
				UpdateEscape();
				timer = 0.0f;
			}
			
			break;
		default:
			return;
		}

		pos_.x = tile_.x * CHA_SIZE;
		pos_.y = tile_.y * CHA_SIZE;
		//timer = timer - moveInterval;
	
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
	//縦48 ,横48
	Rect rect{ pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE };
	DrawRectExtendGraph(pos_.x, pos_.y, pos_.x + CHA_SIZE, pos_.y + CHA_SIZE, animTip_[nowFrame_] * imageSize_, dirArray_[nowDir_] * imageSize_, imageSize_, imageSize_, hImage_, TRUE);

	ImGui::Begin("state");
	ImGui::Text("%s", text);
	ImGui::End();
}
