#include "GameScene.h"
#include "SceneMng.h"
#include "../Obj/Player.h"
#include "../Obj/camera.h"
#include "../Obj/Enemy/s_dragon.h"
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

	auto plObj = std::find_if(_objList.begin(), _objList.end(), [&](std::shared_ptr<Object> obj) { return (*obj).getType() == OBJ_TYPE::PLAYER; });
	//plObj
	lpSceneMng.SetPlObj((*plObj));
	for (auto data : _enemyList)
	{
		(*data).Update();
	}

	getAttackQue();
	CheckHitAttack()(_objList, _attackList);
	CheckHitAttack()(_objList, _attackList);

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
	_objList.emplace_back(new Player({ 400,300 }));
	lpSceneMng.SetPlObj(_objList[0]);
	_objList.emplace_back(new camera());
	_enemyList.emplace_back(new s_dragon());

	lpEffectMng.getEffect("effect/player_attack_fire.efk", "magic_fire", 1.0);

	return false;
}

void GameScene::getAttackQue(void)
{
	_attackList.clear();

	std::vector<atkData> tmpData;

	for (auto data : _objList)
	{
		tmpData.clear();

		// キューの取得
		tmpData = data->getAttackQue();
		
		// キューを保存
		for (auto que : tmpData)
		{
			_attackList.emplace_back(std::make_pair(que, data));
		}
	}

	for (auto data : _enemyList)
	{
		tmpData.clear();

		// キューの取得
		tmpData = data->getAttackQue();

		// キューを保存
		for (auto que : tmpData)
		{
			_attackList.emplace_back(std::make_pair(que, data));
		}
	}
}

