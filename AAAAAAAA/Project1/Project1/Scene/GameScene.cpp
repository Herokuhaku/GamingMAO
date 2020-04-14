#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

std::unique_ptr<BaceScene> GameScene::Update(std::unique_ptr<BaceScene> own)
{
	return own;
}
