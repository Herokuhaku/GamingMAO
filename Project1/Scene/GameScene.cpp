#include "GameScene.h"
#include "SceneMng.h"
#include "../Object/Player.h"
#include "../Object/camera.h"
#include "../Object/Enemy/s_dragon.h"
#include "../Manage/MapMng.h"
#include "../Manage/ItemTrader.h"
#include "../Manage/Menu.h"
#include "../Object/Enemy/EnemyMng.h"
#include "../Object/Attack/AttackMng.h"
#include "../Manage/AttackUI.h"
#include "../Graphic/ImageMng.h"
#include "../Gimmick/GimmickMng.h"
#include "../Gimmick/Rock.h"

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

	lpImageMng.getImage("image/Enemy/small_dragonR.png", "s_dragonR", 128, 128, 4, 5);
	lpImageMng.getImage("image/Enemy/small_dragonL.png", "s_dragonL", 128, 128, 4, 5);

	lpImageMng.getImage("image/Enemy/demonR.png", "demonR", 256, 256, 6, 5);
	lpImageMng.getImage("image/Enemy/demonL.png", "demonL", 256, 256, 6, 5);

	lpImageMng.getImage("image/Enemy/wizardRAttackC.png", "wizardR", 80, 80, 10, 5);
	lpImageMng.getImage("image/Enemy/wizardLAttackC.png", "wizardL", 80, 80, 10, 5);

	lpImageMng.getImage("image/Enemy/sorcerervillainRC.png", "sorcViR", 100, 100, 17, 5);
	lpImageMng.getImage("image/Enemy/sorcerervillainLC.png", "sorcViL", 100, 100, 17, 5);

	lpImageMng.getImage("image/Enemy/exclamationpoint.png", "excPoint", 80, 80, 1, 1);
	lpImageMng.getImage("image/Enemy/questionmark.png", "queMark", 80, 80, 1, 1);

	// アイテム
	// 本(通常)
	lpImageMng.getImage("image/item/Blue_Book.png", "BlueBook");
	lpImageMng.getImage("image/item/Green_Book.png", "GreenBook");
	lpImageMng.getImage("image/item/Red_Book.png", "RedBook");
	// 本(透過)
	lpImageMng.getImage("image/item/TRed_Book.png", "520");
	lpImageMng.getImage("image/item/TGreen_Book.png", "521");
	lpImageMng.getImage("image/item/TBlue_Book.png", "522");
	// 石(通常)
	lpImageMng.getImage("image/item/Blue_Stone.png", "BlueStone");
	lpImageMng.getImage("image/item/Cyan_Stone.png", "CyanStone");
	lpImageMng.getImage("image/item/Green_Stone.png", "GreenStone");
	lpImageMng.getImage("image/item/Magenta_Stone.png", "MagentaStone");
	lpImageMng.getImage("image/item/Red_Stone.png", "RedStone");
	lpImageMng.getImage("image/item/Yellow_Stone.png", "YellowStone");
	// 石(小) 拡大率を変えれば必要なくなるので後程修正
	lpImageMng.getImage("image/item/SRed_Stone.png", "500");
	lpImageMng.getImage("image/item/SGreen_Stone.png", "501");
	lpImageMng.getImage("image/item/SBlue_Stone.png", "502");
	lpImageMng.getImage("image/item/SYellow_Stone.png", "503");
	lpImageMng.getImage("image/item/SMagenta_Stone.png", "504");
	lpImageMng.getImage("image/item/SCyan_Stone.png", "505");
	// 石(透過)
	lpImageMng.getImage("image/item/TRed_Stone.png", "510");
	lpImageMng.getImage("image/item/TGreen_Stone.png", "511");
	lpImageMng.getImage("image/item/TBlue_Stone.png", "512");
	lpImageMng.getImage("image/item/TYellow_Stone.png", "513");
	lpImageMng.getImage("image/item/TMagenta_Stone.png", "514");
	lpImageMng.getImage("image/item/TCyan_Stone.png", "515");

	// ダイナマイト(赤色)
	lpImageMng.getImage("image/item/dynamite.png", "530");
	// 蔓(緑色)
	lpImageMng.getImage("image/item/vine.png", "531");
	// 鳥(青色)
	lpImageMng.getImage("image/item/bard.png", "532");
	// 鍵(黄色)
	lpImageMng.getImage("image/item/key.png", "533");
	// ホース(水色)
	lpImageMng.getImage("image/item/hose.png", "535");
	

	// HPバー
	lpImageMng.getImage("image/HPbar.png", "hp_bar", 6, 12, 3, 1);


	// 攻撃
	lpImageMng.getImage("image/Attack/fireball.png", "fireball", 100, 100, 5, 6);
	lpImageMng.getImage("image/Attack/explosion.png", "explosion", 48, 48, 8, 1);
	lpImageMng.getImage("image/Attack/bubble.png", "bubble");
	lpImageMng.getImage("image/Attack/fruit.png", "fruit", 64, 64, 4, 1);
	lpImageMng.getImage("image/Attack/poison_mist.png", "poison_mist", 320, 120, 1, 8);
	lpImageMng.getImage("image/Attack/ice_wall.png", "ice_wall", 320, 120, 1, 8);
	lpImageMng.getImage("image/Attack/magic_ring.png", "magic_ring", 200, 150, 2, 8);
	lpImageMng.getImage("image/Attack/bomb.png", "bomb", 64, 64, 2, 1);
	lpImageMng.getImage("image/Attack/cloud.png", "cloud");
	lpImageMng.getImage("image/Attack/Lightning.png", "lightning", 240, 240, 8, 1);


	// エフェクト
	lpEffectMng.getEffect("effect/player_attack_fire.efk", "magic_fire", 1.0);
	lpEffectMng.getEffect("effect/player_attack_white_1.efk", "holy", 1.0);

	Init();
}

GameScene::~GameScene()
{
}

std::unique_ptr<BaseScene> GameScene::Update(std::unique_ptr<BaseScene> own)
{
	lpAttackUI.Update();

	for (const auto& data : _objList)
	{
		(*data).Update();
	}
	_cobj->Update();

	lpEnemyMng.Update();

	_gimmickmng->Update();

	lpAtkMng.Update();

	getAttackQue();
	CheckHitAttack()(_objList, _attackList);
	CheckHitAttack()(lpEnemyMng.GetenemyList(), _attackList);


	for (const auto& data : _objList)
	{
		if ((*data).getStage() == lpMapMng.GetnowStage())
		{
			(*data).Draw();
			(*data).attackUpdate();
		}
	}

	lpEnemyMng.Draw();

	_gimmickmng->Draw();

	lpAtkMng.Draw();

	lpTradeMng.Draw();
	ItemDraw();

	lpMapMng.MapDraw();

	lpAttackUI.Draw();

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
		lpTradeMng.BagDraw({ 800,670 }, LAYER::CHAR, { 0,0 }, {1.0,1.0});	// 縦はScreenSize.y - (DrawBoxの長さ/2)
	}
	lpTradeMng.ToolDraw({  800,670 }, LAYER::CHAR, { 0,0 }, {1.0,1.0});

	lpTimeMng.resetFlag();

	return own;
}

bool GameScene::Init(void)
{
	lpTimeMng.TimeInit();

	_objList.clear();
	_objList.emplace_back(std::make_shared<Player>(Vector2(2000,1300), 1, TIME::NOW));
	lpSceneMng.SetPlObj(_objList[0], TIME::NOW);
	_objList.emplace_back(std::make_shared<Player>(Vector2(400, 900), 1, TIME::FTR));
	lpSceneMng.SetPlObj(_objList[1], TIME::FTR);
	_cobj = std::make_shared<camera>();
	lpSceneMng.SetcObj(_cobj);

	_gimmickmng = std::make_unique<GimmickMng>();
	_gimmickmng->AddGimmick(new Rock(Vector2Template<int>(1550, 1100), 1));

	lpMapMng.Init();

	lpEnemyMng.Init();

	lpTradeMng.SetItemList({ 2080,1311 }, ITEM_TYPE::TOOL, COLOR::BLUE,1);
	lpTradeMng.SetItemList({ 2080,1311 }, ITEM_TYPE::TOOL, COLOR::RED,1);
	lpTradeMng.SetItemList({ 2080,1311 }, ITEM_TYPE::TOOL, COLOR::GREEN,1);
	lpTradeMng.SetItemList({ 2080,1311 }, ITEM_TYPE::BOOK, COLOR::BLUE, 1);
	lpTradeMng.SetItemList({ 2080,1311 }, ITEM_TYPE::BOOK, COLOR::RED, 1);
	lpTradeMng.SetItemList({ 2080,1311 }, ITEM_TYPE::BOOK, COLOR::GREEN, 1);
	


	return false;
}

void GameScene::getAttackQue(void)
{
	_attackList.clear();

	std::vector<atkData> tmpData;

	for (const auto& data : _objList)
	{
		tmpData.clear();

		// キューの取得
		tmpData = data->getAttackQue();
		
		// キューを保存
		for (const auto& que : tmpData)
		{
			_attackList.emplace_back(std::make_pair(que, data));
		}
	}

	for (const auto& data : lpEnemyMng.GetenemyList())
	{
		tmpData.clear();

		// キューの取得
		tmpData = data->getAttackQue();

		// キューを保存
		for (const auto& que : tmpData)
		{
			_attackList.emplace_back(std::make_pair(que, data));
		}
	}

	for (const auto& data : lpAtkMng.GetAttackObjList())
	{
		tmpData.clear();

		// キューの取得
		tmpData = data->getAttackQue();

		// キューを保存
		for (const auto& que : tmpData)
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
			lpStrAdd.AddStringDraw(_no.c_str(), "SQUARE_BIG", pos.x + (i * 75) + 20, pos.y-25, 0xffff00, DRAW_TO_LEFT);
		}
		else
		{
			lpImageMng.AddBackDraw({ lpImageMng.getImage(no)[0], pos.x - (3 * 75) + (i*75),pos.y + 50, 1.0, 0.0, LAYER::CHAR,150, DX_BLENDMODE_NOBLEND, 0 });
			lpStrAdd.AddStringDraw(_no.c_str(), "SQUARE_BIG", pos.x - (3 * 75) + (i * 75) +20, pos.y + 25, 0xffff00, DRAW_TO_LEFT);
		}
		tmp++;
	}
}

