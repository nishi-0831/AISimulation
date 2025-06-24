#include "Stage.h"
#include "global.h"


Stage* Stage::instance_ = nullptr;
Stage::Stage()
{
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			
			
			{
				stage_[{x, y}] = Tile::ROAD;
				//stage_.insert(std::make_pair<Point, Tile>({ x,y }, Tile::ROAD));
			}
			
		}
	}
	for (int i = 0;i < wallPoint.size();i++)
	{
		stage_[wallPoint[i]] = Tile::WALL;
	}
	stage_[escapePoint] = Tile::ESCAPEPOINT;
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	//ŠO˜g‚Ì•`‰æ
	//DrawBox(0, 0, CHA_SIZE * (STAGE_WIDTH - 1), CHA_SIZE * (STAGE_HEIGHT-1), GetColor(0, 155, 255), false,7);
	//DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(200, 255, 255), FALSE);

	//for(auto tile:stage_)
	DrawBox(escapePoint.x * CHA_SIZE, escapePoint.y * CHA_SIZE, (escapePoint.x + 1) * CHA_SIZE, (escapePoint.y + 1) * CHA_SIZE, GetColor(122, 122, 122), TRUE);
	//ƒXƒe[ƒW‚Ì•`‰æ
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			DrawBox(x * CHA_SIZE, y * CHA_SIZE, (x + 1) * CHA_SIZE, (y + 1) * CHA_SIZE, GetColor(0, 0, 125), FALSE);
			//ŠO˜g
			if (x == 0 || x == STAGE_WIDTH - 1 || y == 0 || y == STAGE_HEIGHT - 1)
			{
				DrawBox(x * CHA_SIZE, y * CHA_SIZE, (x + 1) * CHA_SIZE, (y + 1) * CHA_SIZE, GetColor(255, 255, 255), TRUE);	
			}
			
			
		}
	}

}
