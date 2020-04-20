#include "GameScene.h"
#include "SceneMng.h"
#include "../Obj/Player.h"
#include "../MapMng.h"

GameScene::GameScene()
{
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
	//lpMapMng.MapUpdate();

	return own;
}

bool GameScene::Init(void)
{
	_objList.clear();
	_objList.emplace_back(new Player({ 400,300 }));

	return false;
}
