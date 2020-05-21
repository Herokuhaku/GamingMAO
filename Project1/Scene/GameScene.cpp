#include "GameScene.h"
#include "SceneMng.h"
#include "../Object/Player.h"
#include "../Object/camera.h"
#include "../Object/Enemy/s_dragon.h"
#include "../Manage/MapMng.h"
#include "../Manage/ItemTrader.h"
#include "../Manage/Menu.h"
#include "../Object/Enemy/EnemyMng.h"

GameScene::GameScene()
{
	lpEnemyMng;
	
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

	// アイテム
	// 本
	lpImageMng.getImage("image/item/Blue_Book.png", "BlueBook");
	lpImageMng.getImage("image/item/Green_Book.png", "GreenBook");
	lpImageMng.getImage("image/item/Red_Book.png", "RedBook");
	// 石(通常)
	lpImageMng.getImage("image/item/Blue_Stone.png", "BlueStone");
	lpImageMng.getImage("image/item/Cyan_Stone.png", "CyanStone");
	lpImageMng.getImage("image/item/Green_Stone.png", "GreenStone");
	lpImageMng.getImage("image/item/Magenta_Stone.png", "MagentaStone");
	lpImageMng.getImage("image/item/Red_Stone.png", "RedStone");
	lpImageMng.getImage("image/item/Yellow_Stone.png", "YellowStone");
	// 石(小)
	lpImageMng.getImage("image/item/SRed_Stone.png", "500");
	lpImageMng.getImage("image/item/SGreen_Stone.png", "501");
	lpImageMng.getImage("image/item/SBlue_Stone.png", "502");
	lpImageMng.getImage("image/item/SCyan_Stone.png", "503");
	lpImageMng.getImage("image/item/SMagenta_Stone.png", "504");
	lpImageMng.getImage("image/item/SYellow_Stone.png", "505");

	// HPバー
	lpImageMng.getImage("image/HPbar.png", "hp_bar", 6, 12, 3, 1);


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

	lpEnemyMng.Update();

	getAttackQue();
	CheckHitAttack()(_objList, _attackList);
	CheckHitAttack()(lpEnemyMng.GetenemyList(), _attackList);


	for (auto data : _objList)
	{
		if ((*data).getStage() == lpMapMng.GetnowStage())
		{
			(*data).Draw();
			(*data).attackUpdate();
		}
	}

	lpEnemyMng.Draw();

	lpTradeMng.Draw();
	ItemDraw();

	lpMapMng.MapDraw();

	// 死んでいるプレイヤーを探す
	auto plDead = std::find_if(_objList.begin(), _objList.end(), [](std::shared_ptr<Object> obj) { return (obj->getObjType() == OBJ_TYPE::PLAYER && obj->getState().first == OBJ_STATE::DEAD); });

	// 死んだときの処理
	if (plDead != _objList.end())
	{
		lpImageMng.Draw(lpSceneMng.GetNum(), false);
		own = std::make_unique<GameOverScene>();
	}

	if (!lpMenuMng.GetMixFlag())
	{
		lpTradeMng.BagDraw({ 600,650 }, LAYER::CHAR, 200);

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

	lpEnemyMng.Init();

	lpTradeMng.SetItemList({ 400,1300 }, ITEM_TYPE::STONE, COLOR_TYPE::BLUE);
	lpTradeMng.SetItemList({ 400,1500 }, ITEM_TYPE::STONE, COLOR_TYPE::RED);
	lpTradeMng.SetItemList({ 400,1700 }, ITEM_TYPE::STONE, COLOR_TYPE::GREEN);
	
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

	for (auto data : lpEnemyMng.GetenemyList())
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

void GameScene::ItemDraw(void)
{// 描画用データ　画像ID, 座標x, y, 拡大率、角度, レイヤー, zオーダー、ブレンド、パラメータ
	Vector2 pos = { 500,650 };
	int tmp = 500;
	std::string no;
	for (int i = 0;i < 6;i++)
	{
		no = std::to_string(tmp);
		std::string _no = std::to_string(lpTradeMng.getrock().at(i));
		if (i < 3)
		{
			lpImageMng.AddBackDraw({ lpImageMng.getImage(no)[0], pos.x + (i * 75),pos.y, 1.0, 0.0, LAYER::CHAR,150, DX_BLENDMODE_NOBLEND, 0 });
			lpStrAdd.AddDraw(_no.c_str(), pos.x + (i * 75) + 20, pos.y-25, 0xffff00, DRAW_TO_LEFT);
		}
		else
		{
			lpImageMng.AddBackDraw({ lpImageMng.getImage(no)[0], pos.x - (3 * 75) + (i*75),pos.y + 50, 1.0, 0.0, LAYER::CHAR,150, DX_BLENDMODE_NOBLEND, 0 });
			lpStrAdd.AddDraw(_no.c_str(), pos.x - (3 * 75) + (i * 75) +20, pos.y + 25, 0xffff00, DRAW_TO_LEFT);
		}
		tmp++;
	}
}

