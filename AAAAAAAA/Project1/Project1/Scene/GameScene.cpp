#include "GameScene.h"
#include "SceneMng.h"
#include "../Object/Player.h"

GameScene::GameScene()
{
	lpImageMng.getImage("image/player.png", "splayer1", 85,90, 2,2);	// size.x,y,cnx.y
	Init();
}

GameScene::~GameScene()
{
}

std::unique_ptr<BaceScene> GameScene::Update(std::unique_ptr<BaceScene> own)
{

	for (auto data : _objList)
	{
		(*data).Update();
	}

	for (auto data : _objList)
	{
		(*data).Draw();
	}

	return own;
}

bool GameScene::Init(void)
{
	_objList.clear();
	_objList.emplace_back(new Player({ 400,300 }));

	return false;
}
