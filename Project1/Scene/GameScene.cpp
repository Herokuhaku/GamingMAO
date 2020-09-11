#include "GameScene.h"
#include "SceneMng.h"
#include "../Object/Player.h"
#include "../Object/camera.h"
#include "../Object/Enemy/s_dragon.h"
#include "../Manage/MapMng.h"
#include "../Manage/ItemTrader.h"
#include "../Object/Enemy/EnemyMng.h"
#include "../Object/Attack/AttackMng.h"
#include "../Manage/AttackUI.h"
#include "../Graphic/ImageMng.h"
#include "../Gimmick/GimmickMng.h"
#include "../Menu/MenuExecuter.h"
#include "../Gimmick/Rock.h"
#include "../Gimmick/Door.h"
#include "../Object/Barrier/BarrierMng.h"
#include "../Object/Attack/white/StopTime.h"
#include "../Manage/DamageDisplay.h"
#include "../Audio/AudioContainer.h"
#include "../Manage/SignMng.h"

namespace
{
	AudioContainer _audio;
}

GameScene::GameScene(const Vector2& pos, int stage)
{
	lpEnemyMng;
	SignMng::GetInstance();
	
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

	lpImageMng.getImage("image/Enemy/sorcerervillainRC.png", "sorcViR", 100, 100, 17, 6);
	lpImageMng.getImage("image/Enemy/sorcerervillainLC.png", "sorcViL", 100, 100, 17, 6);

	lpImageMng.getImage("image/Enemy/exclamationpoint.png", "excPoint", 80, 80, 1, 1);
	lpImageMng.getImage("image/Enemy/questionmark.png", "queMark", 80, 80, 1, 1);

	// アイテム
	// 本(通常)
	lpImageMng.getImage("image/item/Blue_Book.png", "BlueBook");
	lpImageMng.getImage("image/item/Green_Book.png", "GreenBook");
	lpImageMng.getImage("image/item/Red_Book.png", "RedBook");
	// 本(透過)
	lpImageMng.getImage("image/item/TRed_Book.png", "520");		// 赤の本
	lpImageMng.getImage("image/item/TGreen_Book.png", "521");	// 緑の本
	lpImageMng.getImage("image/item/TBlue_Book.png", "522");	// 青の本
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
	// パウダー(紫色)
	lpImageMng.getImage("image/item/powder.png", "534");
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
	lpImageMng.getImage("image/Attack/tree.png", "tree", 250, 150, 1, 5);
	lpImageMng.getImage("image/Attack/spark.png", "spark", 80, 80, 8, 1);
	lpImageMng.getImage("image/Attack/clock_stop.png", "clock_stop", 480, 480, 5, 3);
	lpImageMng.getImage("image/Attack/star.png", "star", 96, 64, 6, 1);


	// エフェクト
	lpEffectMng.getEffect("effect/player_attack_fire.efk", "magic_fire", 1.0);
	lpEffectMng.getEffect("effect/player_attack_white_1.efk", "holy", 1.0);

	// 状態異常
	lpImageMng.getImage("image/Attack/iceblock.png", "ice_effect", 100, 100, 4, 1);

	_objList.clear();
	_objList.emplace_back(std::make_shared<Player>(Vector2(pos.x, pos.y), stage, TIME::FTR, this));
	lpSceneMng.SetPlObj(_objList[0], TIME::FTR);
	_objList.emplace_back(std::make_shared<Player>(Vector2(pos.x, pos.y), stage, TIME::NOW, this));
	lpSceneMng.SetPlObj(_objList[1], TIME::NOW);
	_cobj = std::make_shared<camera>();
	lpSceneMng.SetcObj(_cobj);

	

	Init(stage);
}

GameScene::~GameScene()
{
	DamageDisplay::GetInstance().DeleteAll();
	lpAtkMng.DeleteAll();
}

std::unique_ptr<BaseScene> GameScene::Update(std::unique_ptr<BaseScene> own)
{
	own = (this->*_update)(std::move(own));
	return own;
}

std::shared_ptr<MenuExecuter>& GameScene::GetMenuExecuter(void)
{
	return _menu;
}

std::shared_ptr<BarrierMng>& GameScene::GetBarrierMng(void)
{
	return _barrierMng;
}

std::shared_ptr<Object> GameScene::FindObject(Object* obj)
{
	for (const auto& ol : _objList)
	{
		if (obj == ol.get())
		{
			return ol;
		}
	}

	auto enemyl = lpEnemyMng.GetenemyList();

	for (const auto& el : enemyl)
	{
		std::shared_ptr<Object> eo = std::dynamic_pointer_cast<Object>(el);
		if (obj == eo.get())
		{
			return eo;
		}
	}

	return nullptr;
}

bool GameScene::Init(int stage)
{
	GimmickMng::DeleteAll();
	//lpTradeMng.DeleteAll();

	lpTimeMng.TimeInit();

	lpAttackUI.Reset();

	_gimmickMng = std::make_unique<GimmickMng>();
	_gimmickMng->AddGimmick(new Rock(Vector2Template<int>(1550, 1100), 1));
	_gimmickMng->AddGimmick(new Door(Vector2Template<int>(192,532), 4));
	_menu.reset(new MenuExecuter(this));

	_barrierMng.reset(new BarrierMng(this));

	_update = &GameScene::NormalUpdate;

	lpMapMng.Init();

	lpEnemyMng.Init(stage);

	lpMapMng.StageTrans(stage);

	//lpTradeMng.SetItemList({ 200,1311 }, ITEM_TYPE::STONE, COLOR::BLUE,1);
	//lpTradeMng.SetItemList({ 200,1311 }, ITEM_TYPE::STONE, COLOR::RED,1);
	//lpTradeMng.SetItemList({ 200,1311 }, ITEM_TYPE::STONE, COLOR::GREEN,1);
	lpTradeMng.SetItemList({ 300,1311 }, ITEM_TYPE::BOOK, COLOR::RED, 2);
	lpTradeMng.SetItemList({ 200,1311 }, ITEM_TYPE::BOOK, COLOR::RED, 1);
	//lpTradeMng.SetItemList({ 200,1311 }, ITEM_TYPE::BOOK, COLOR::GREEN, 1);
	lpTradeMng.SetItemList({ 200,400 }, ITEM_TYPE::BOOK, COLOR::BLUE, 6);
	
	EffectData effect;
	effect.reserve(16);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[0], 3);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[1], 6);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[2], 9);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[3], 12);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[4], 15);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[5], 25);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[6], 35);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[7], 45);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[8], 48);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[9], 51);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[10], 54);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[11], 57);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[12], 60);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[13], 63);
	effect.emplace_back(lpImageMng.getImage("clock_stop")[14], 83);
	effect.emplace_back(0, -1);

	lpImageMng.setEffect("clock_stop", effect);

	_audio.LoadSound("sound/BGM/ms.mp3", "ms", 10);
	_audio.ChangeVolume("ms", 110);
	StopSoundMem(_audio.GetSound("ms"));
	PlaySoundMem(_audio.GetSound("ms"), DX_PLAYTYPE_LOOP, true);
	
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
			lpImageMng.AddBackDraw({ lpImageMng.getImage(no)[0], pos.x + (i * 75),pos.y, 1.0, 0.0, LAYER::CHAR,150, DX_BLENDMODE_NOBLEND, 0, true });
			lpStrAdd.AddStringDraw(_no.c_str(), "SQUARE_BIG", pos.x + (i * 75) + 20, pos.y-25, 0xffff00, DRAW_TO_LEFT);
		}
		else
		{
			lpImageMng.AddBackDraw({ lpImageMng.getImage(no)[0], pos.x - (3 * 75) + (i*75),pos.y + 50, 1.0, 0.0, LAYER::CHAR,150, DX_BLENDMODE_NOBLEND, 0, true });
			lpStrAdd.AddStringDraw(_no.c_str(), "SQUARE_BIG", pos.x - (3 * 75) + (i * 75) +20, pos.y + 25, 0xffff00, DRAW_TO_LEFT);
		}
		tmp++;
	}
}

std::unique_ptr<BaseScene> GameScene::NormalUpdate(std::unique_ptr<BaseScene> own)
{
	if (!lpSignMng.IsActive())
	{
		std::dynamic_pointer_cast<Player>(lpSceneMng.GetPlObj2(TIME::FTR))->GetStopTime()->Update();

		lpAttackUI.Update();

		for (const auto& data : _objList)
		{
			if ((*data).CanMoveWithEffect())
			{
				(*data).Update();
			}
			(*data).InvUpdate();
			(*data).UpdateStateEffect();
		}
		_cobj->Update();

		lpEnemyMng.Update();

		_barrierMng->Update();

		_gimmickMng->Update();

		lpAtkMng.Update();

		_menu->Update();

		lpTradeMng.ListUpdate();


		getAttackQue();
		CheckHitAttack()(_barrierMng->GetBarrier(), _attackList);
		CheckHitAttack()(_objList, _attackList);
		CheckHitAttack()(lpEnemyMng.GetenemyList(), _attackList);
	}

	if (!_menu->IsActive())
	{
		lpSignMng.Check();
	}
	std::dynamic_pointer_cast<Player>(lpSceneMng.GetPlObj2(TIME::FTR))->GetStopTime()->Draw();

	for (const auto& data : _objList)
	{
		if ((*data).getStage() == lpMapMng.GetnowStage())
		{
			(*data).Draw();
			(*data).attackUpdate();
		}
	}

	lpEnemyMng.Draw();

	_barrierMng->Draw();

	_gimmickMng->Draw();

	lpAtkMng.Draw();

	lpTradeMng.Draw();
	ItemDraw();

	lpMapMng.MapDraw();

	lpAttackUI.Draw();

	_menu->Draw();

	lpSignMng.Draw();

	// 死んでいるプレイヤーを探す
	auto plDead = std::find_if(_objList.begin(), _objList.end(), [](std::shared_ptr<Object> obj) { return (obj->getObjType() == OBJ_TYPE::PLAYER && obj->getState().first == OBJ_STATE::DEAD); });

	// 死んだときの処理
	if (plDead != _objList.end())
	{
		lpImageMng.Draw(lpSceneMng.GetNum(), false);
		StopSoundMem(_audio.GetSound("ms"));
		own = std::make_unique<GameOverScene>();
	}

	lpTradeMng.BagDraw({ 800,670 }, LAYER::CHAR, { 0,0 }, { 1.0,1.0 });	// 縦はScreenSize.y - (DrawBoxの長さ/2)
	lpTradeMng.ToolDraw({ 800,670 }, LAYER::CHAR, { 0,0 }, { 1.0,1.0 });

	lpTimeMng.resetFlag();

	DamageDisplay::GetInstance().Draw();

	if (std::dynamic_pointer_cast<Player>(lpSceneMng.GetPlObj2(TIME::FTR))->IsTimeStoped())
	{
		_update = &GameScene::StopedUpdate;
	}

	return own;
}

std::unique_ptr<BaseScene> GameScene::StopedUpdate(std::unique_ptr<BaseScene> own)
{
	if (!lpSignMng.IsActive())
	{
		std::shared_ptr<Object> player = lpSceneMng.GetPlObj2(TIME::FTR);
		std::dynamic_pointer_cast<Player>(player)->GetStopTime()->Update();

		lpAttackUI.Update();

		if (player->CanMoveWithEffect())
		{
			player->Update();
		}
		player->InvUpdate();
		player->UpdateStateEffect();

		_cobj->Update();

		_barrierMng->Update();

		_menu->Update();

		getAttackQue();
		CheckHitAttack()(_barrierMng->GetBarrier(), _attackList);
		CheckHitAttack()(_objList, _attackList);
		CheckHitAttack()(lpEnemyMng.GetenemyList(), _attackList);
	}

	if (!_menu->IsActive())
	{
		lpSignMng.Check();
	}
	std::dynamic_pointer_cast<Player>(lpSceneMng.GetPlObj2(TIME::FTR))->GetStopTime()->Draw();

	for (const auto& data : _objList)
	{
		if ((*data).getStage() == lpMapMng.GetnowStage())
		{
			(*data).Draw();
		}
	}

	lpEnemyMng.Draw();

	_barrierMng->Draw();

	//_gimmickMng->Draw();

	lpAtkMng.Draw();

	lpTradeMng.Draw();
	ItemDraw();

	lpMapMng.MapDraw();

	lpAttackUI.Draw();

	_menu->Draw();

	lpSignMng.Draw();

	// 死んでいるプレイヤーを探す
	auto plDead = std::find_if(_objList.begin(), _objList.end(), [](std::shared_ptr<Object> obj) { return (obj->getObjType() == OBJ_TYPE::PLAYER && obj->getState().first == OBJ_STATE::DEAD); });

	// 死んだときの処理
	if (plDead != _objList.end())
	{
		lpImageMng.Draw(lpSceneMng.GetNum(), false);
		StopSoundMem(_audio.GetSound("ms"));
		own = std::make_unique<GameOverScene>();
	}

	//if (!lpMenuMng.GetMixFlag())
	//{
	lpTradeMng.BagDraw({ 800,670 }, LAYER::CHAR, { 0,0 }, { 1.0,1.0 });	// 縦はScreenSize.y - (DrawBoxの長さ/2)
	//}
	lpTradeMng.ToolDraw({ 800,670 }, LAYER::CHAR, { 0,0 }, { 1.0,1.0 });

	lpTimeMng.resetFlag();

	DamageDisplay::GetInstance().Draw();

	if (!std::dynamic_pointer_cast<Player>(lpSceneMng.GetPlObj2(TIME::FTR))->IsTimeStoped())
	{
		_update = &GameScene::NormalUpdate;
	}

	return own;
}

