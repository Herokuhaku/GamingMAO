#include "GameScene.h"

GameScene::GameScene()
{
	player = new Player({ 100,600 });
}

GameScene::~GameScene()
{
}

std::unique_ptr<BaceScene> GameScene::Update(std::unique_ptr<BaceScene> own)
{
	player->Update();
	
	return own;
}
