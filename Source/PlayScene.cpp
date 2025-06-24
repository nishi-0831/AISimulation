#include "PlayScene.h"
#include <DxLib.h>
#include "../Stage.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../Input.h"
#include "../ImGuiSample.h"
//#include "../Library/Time.h"

PlayScene::PlayScene()
{
	//Stage* stage = new Stage();
	//new Stage();
	Stage::GetInstance();
	new Player();
	new Enemy();
	//Time::Init();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	//Time::Refresh();
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
	Input::KeyStateUpdate();
}

void PlayScene::Draw()
{
	//DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, GetColor(200, 255, 255), FALSE);
	ClearDrawScreen();
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
