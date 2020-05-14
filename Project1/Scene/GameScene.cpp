#include "GameScene.h"
#include "SceneMng.h"
#include "../Object/Player.h"
#include "../Object/camera.h"
#include "../Object/Enemy/s_dragon.h"
#include "../Manage/MapMng.h"
#include "../Manage/ItemTrader.h"
#include "../Manage/Menu.h"

GameScene::GameScene()
{
	// 画像

	// プレイヤー
	lpImageMng.getImage("image/player.png", "player", 85, 90, 2, 2);
	lpImageMng.getImage("image/player_walk.png", "player_walk", 85, 90, 8, 2);
	lpImageMng.getImage("image/player_dash.png", "player_dash", 85, 90, 2, 2);
	lpImageMng.getImage("image/player_jump.png", "player_jump", 85, 90, 2, 2);
	lpImageMng.getImage("image/player_attack.png", "player_attack", 85, 90, 2, 12);
	lpImageMng.getImage("image/player_damaged.png", "player_damaged", 85, 90, 2, 3);

	lpImageMng.getImage("image/small_dragonR.png", "s_dragonR", 128, 128, 4, 5);
	lpImageMng.getImage("image/small_dragonL.png", "s_dragonL", 128, 128, 4, 5);
	lpImageMng.getImage("image/exclamationpoint.png", "excPoint", 80, 80, 1, 1);
	lpImageMng.getImage("image/questionmark.png", "queMark", 80, 80, 1, 1);


	// HPバー
	lpImageMng.getImage("image/HPbar.png", "hp_bar", 6, 12, 3, 1);


	// アイテム

	lpImageMng.getImage("image/BlueBook.png", "BlueBook");

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

	for (auto data : _enemyList)
	{
		(*data).Update();
	}

	getAttackQue();
	CheckHitAttack()(_objList, _attackList);
	CheckHitAttack()(_enemyList, _attackList);


	for (auto data : _objList)
	{
		if ((*data).getStage() == lpMapMng.GetnowStage())
		{
			(*data).Draw();
			(*data).attackUpdate();
		}
	}

	for (auto data : _enemyList)
	{
		if ((*data).getStage() == lpMapMng.GetnowStage())
		{
			(*data).Draw();
		}
	}

	lpTradeMng.Draw();

	lpMapMng.MapDraw();

	// 死んでいるプレイヤーを探す
	auto plDead = std::find_if(_objList.begin(), _objList.end(), [](std::shared_ptr<Object> obj) { return (obj->getType() == OBJ_TYPE::PLAYER && obj->getState().first == OBJ_STATE::DEAD); });

	// 死んだときの処理
	if (plDead != _objList.end())
	{
		lpImageMng.Draw(lpSceneMng.GetNum(), false);
		own = std::make_unique<GameOverScene>();
	}

	if (!lpMenuMng.GetMixFlag())
	{
		lpTradeMng.BagDraw({ 800,680 }, LAYER::CHAR, 100);
	}

	lpTimeMng.resetFlag();

	return own;
}

bool GameScene::Init(void)
{
	_objList.clear();
	_objList.emplace_back(new Player({ 400,900 }, 1, TIME::NOW));
	lpSceneMng.SetPlObj(_objList[0], TIME::NOW);
	_objList.emplace_back(new Player({ 400,900 }, 1, TIME::FTR));
	lpSceneMng.SetPlObj(_objList[1], TIME::FTR);
	_objList.emplace_back(new camera());
	_enemyList.emplace_back(new s_dragon());

	lpTradeMng.SetItemList({ 400,1300 }, ITEM_TYPE::BOOK, COLOR_TYPE::BLUE);
	
	lpTimeMng.TimeInit();

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

