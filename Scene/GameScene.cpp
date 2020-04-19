#include "GameScene.h"
#include "SceneMng.h"
#include "../Obj/Player.h"
//#include "../Obj/Enemy/Enemy.h
#include "../Obj/Enemy/s_dragon.h"
#include <algorithm>

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

	auto plObj = std::find_if(_objList.begin(), _objList.end(), [&](std::shared_ptr<Object> obj) { return (*obj).getType() == OBJ_TYPE::PLAYER; });
	//plObj
	lpSceneMng.SetPlObj((*plObj));
	for (auto data : _enemyList)
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
	_enemyList.emplace_back(new s_dragon());
	return false;
}
