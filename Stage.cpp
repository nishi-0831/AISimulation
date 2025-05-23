#include "Stage.h"
#include "global.h"



Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	//�O�g�̕`��
	DrawBox(0, 0, CHA_SIZE * (STAGE_WIDTH - 1), CHA_SIZE * (STAGE_HEIGHT-1), GetColor(0, 155, 255), false,7);


	//�X�e�[�W�̕`��
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			DrawBox(x * CHA_SIZE, y * CHA_SIZE, (x + 1) * CHA_SIZE, (y + 1) * CHA_SIZE, GetColor(0, 0, 125), FALSE);
			if (x == 0 || x == STAGE_WIDTH - 1 || y == 0 || y == STAGE_HEIGHT - 1)
			{
				//DrawBox(x * CHA_SIZE, y * CHA_SIZE, CHA_SIZE, CHA_SIZE, GetColor(135, 125, 0), false);
				//�O�g
				DrawBox(x * CHA_SIZE, y * CHA_SIZE, (x + 1) * CHA_SIZE, (y + 1) * CHA_SIZE, GetColor(255, 255, 255), TRUE);
			}
			
			
		}
	}
}
