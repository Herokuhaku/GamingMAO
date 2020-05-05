#include "GameScene.h"
#include "SceneMng.h"
#include "../Object/Player.h"
//#include "../Obj/Enemy/Enemy.h
#include "../Object/Enemy/s_dragon.h"
#include <algorithm>
#include "../MapMng.h"
#include "../Object/camera.h"


GameScene::GameScene()
{

	// 画像

	lpImageMng.getImage("image/player.png", "player", 85, 90, 2, 2);
	lpImageMng.getImage("image/player_walk.png", "player_walk", 85, 90, 8, 2);
	lpImageMng.getImage("image/player_dash.png", "player_dash", 85, 90, 2, 2);
	lpImageMng.getImage("image/player_jump.png", "player_jump", 85, 90, 2, 2);
	lpImageMng.getImage("image/player_attack.png", "player_attack", 85, 90, 2, 12);



	lpImageMng.getImage("image/small_dragonR.png", "s_dragonR", 128, 128, 4, 5);
	lpImageMng.getImage("image/small_dragonL.png", "s_dragonL", 128, 128, 4, 5);
	lpImageMng.getImage("image/exclamationpoint.png", "excPoint", 80, 80, 1, 1);
	lpImageMng.getImage("image/questionmark.png", "queMark", 80, 80, 1, 1);

	// エフェクト
	lpEffectMng.getEffect("effect/player_attack_fire.efk", "magic_fire", 1.0);


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
		lpMapMng.MapDraw();
	return own;
}

bool GameScene::Init(void)
{
	_objList.clear();
	_objList.emplace_back(new Player({ 400,1200 }));
	lpSceneMng.SetPlObj(_objList[0]);
	_objList.emplace_back(new camera());
	_enemyList.emplace_back(new s_dragon());


	return false;
}
