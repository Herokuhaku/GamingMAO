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
	lpImageMng.getImage("image/player_dameged.png", "player_damaged", 85, 90, 2, 3);

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

	if ((lpKeyMng.getOldBuf()[KEY_INPUT_LSHIFT] && !lpKeyMng.getBuf()[KEY_INPUT_LSHIFT]))
	{
		lpTimeMng.setTime(static_cast<TIME>(1 - static_cast<int>(lpTimeMng.getTime())));
	}

	auto plObj = std::find_if(_objList.begin(), _objList.end(), [&](std::shared_ptr<Object> obj) { return ((*obj).getType() == OBJ_TYPE::PLAYER && (*obj).getTimeLine() == lpTimeMng.getTime()); });
	//plObj
	for (auto data : _enemyList)
	{
		(*data).Update();
	}

	getAttackQue();
	CheckHitAttack()(_objList, _attackList);
	CheckHitAttack()(_enemyList, _attackList);



	for (auto data : _objList)
	{
		(*data).Draw();
		(*data).attackUpdate();
	}

	lpTradeMng.Draw();
	if (!lpMenuMng.GetMixFlag())
	{
		lpTradeMng.BagDraw({ 200,300 }, LAYER::CHAR);
	}
	lpMapMng.MapDraw();

	return own;
}

bool GameScene::Init(void)
{
	_objList.clear();
	_objList.emplace_back(new Player({ 400,900 }, 1, TIME::NOW));
	lpSceneMng.SetPlObj(_objList[0]);
	_objList.emplace_back(new Player({ 400,900 }, 1, TIME::FTR));
	_objList.emplace_back(new camera());
	_enemyList.emplace_back(new s_dragon());

	lpTradeMng.SetItemList({ 400,1300 }, ITEM_TYPE::BOOK, COLOR_TYPE::BLUE);

	

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

