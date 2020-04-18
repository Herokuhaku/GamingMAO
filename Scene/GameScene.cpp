#include "GameScene.h"

GameScene::GameScene()
{
//	player = new Player({ 300,400 });
	//enemy = new Enemy({ 300,400 }, 0.0, TIME::FTR, 0, OBJ_TYPE::ENEMY, { OBJ_STATE::NORMAL,DIR::RIGHT });
	test = new s_dragon({ 300,400 }, 0.0, TIME::FTR, 0, OBJ_TYPE::ENEMY, { OBJ_STATE::NORMAL,DIR::RIGHT });
}

GameScene::~GameScene()
{
}

std::unique_ptr<BaceScene> GameScene::Update(std::unique_ptr<BaceScene> own)
{
//	player->Update();
	test->Update();
	return own;
}
