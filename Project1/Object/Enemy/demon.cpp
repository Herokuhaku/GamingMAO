#include "demon.h"
#include "../../Scene/SceneMng.h"
#include "../../Graphic/ImageMng.h"

void demon::Update(void)
{
	Enemy::Update();
}

//s_dragon::s_dragon(Vector2Template<int> pos, double rad, TIME time, int stage, OBJ_TYPE type, std::pair<OBJ_STATE, DIR> state_dir)
demon::demon(Vector2 pos, int stage)
	{
	_pos = pos;
	_stage = stage;
	_state_dir = { OBJ_STATE::NORMAL,DIR::RIGHT };
	setHP(100);
	setHitOffset({ 55, 55, 100, 0 });
	
	while (!lpMapMng.getHitMap(_pos, _stage))
	{
		_pos.y += 1;
	}
	Init();
}

demon::demon(Vector2 pos, int stage, int pPos, bool flag)
{
	_pos = pos;
	_stage = stage;
	_etype = ENEMY_TYPE::s_dragon;
	_pPos = pPos;
	_state_dir = { OBJ_STATE::NORMAL,DIR::RIGHT };
	setHP(100);
	setHitOffset({ 55, 55, 100, 0 });
	if (flag)
	{
		while (!lpMapMng.getHitMap(_pos, _stage))
		{
			_pos.y += 1;
		}
	}
	Init();
}

demon::~demon()
{
}

void demon::Init(void)
{
	AnmVec dataR;
	AnmVec dataL;
	int animCnt = 15;
// 左右のアニメーションの登録-------------------------------------------
	for (int i = 0; i < 2; i++)
	{
		dataR.emplace_back(lpImageMng.getImage("demonR")[6 + i], animCnt + i * animCnt);
		dataL.emplace_back(lpImageMng.getImage("demonL")[6 + i], animCnt + i * animCnt);
	}
	setAnm({ OBJ_STATE::NORMAL,DIR::RIGHT }, dataR);
	setAnm({ OBJ_STATE::NORMAL,DIR::LEFT }, dataL);

	animCnt = 10;
	for (int i = 0; i < 6; i++)
	{
		dataR.emplace_back(lpImageMng.getImage("demonR")[i], animCnt + i * animCnt);
		dataL.emplace_back(lpImageMng.getImage("demonL")[i], animCnt + i * animCnt);
	}
	setAnm({ OBJ_STATE::WALK,DIR::RIGHT }, dataR);
	setAnm({ OBJ_STATE::WALK,DIR::LEFT }, dataL);

	//for (int i = 0; i < 4; i++)
	{
		int i = 0;
		dataR.emplace_back(lpImageMng.getImage("demonR")[24 + i], 10);
		dataL.emplace_back(lpImageMng.getImage("demonL")[24 + i], 10);
		i++;
		dataR.emplace_back(lpImageMng.getImage("demonR")[24 + i], 15);
		dataL.emplace_back(lpImageMng.getImage("demonL")[24 + i], 15);
		i++;
		dataR.emplace_back(lpImageMng.getImage("demonR")[24 + i], 30);
		dataL.emplace_back(lpImageMng.getImage("demonL")[24 + i], 30);
		i++;
		dataR.emplace_back(lpImageMng.getImage("demonR")[24 + i], 40);
		dataL.emplace_back(lpImageMng.getImage("demonL")[24 + i], 40);
	}
	dataR.emplace_back(-1, 0);
	dataL.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK,DIR::RIGHT }, dataR);
	setAnm({ OBJ_STATE::ATTACK,DIR::LEFT }, dataL);

	for (int i = 0; i < 2; i++)
	{
		dataR.emplace_back(lpImageMng.getImage("demonR")[12 + i], animCnt + i * animCnt);
		dataL.emplace_back(lpImageMng.getImage("demonL")[12 + i], animCnt + i * animCnt);
	}
	dataR.emplace_back(-1,0);
	dataL.emplace_back(-1,0);
	setAnm({ OBJ_STATE::DAMAGE,DIR::RIGHT }, dataR);
	setAnm({ OBJ_STATE::DAMAGE,DIR::LEFT }, dataL);

	for (int i = 0; i < 5; i++)
	{
		dataR.emplace_back(lpImageMng.getImage("demonR")[18 + i], animCnt + i * animCnt);
		dataL.emplace_back(lpImageMng.getImage("demonL")[18 + i], animCnt + i * animCnt);
	}
	dataR.emplace_back(-1,2828);
	dataL.emplace_back(-1, 2828);
	setAnm({ OBJ_STATE::DEAD,DIR::RIGHT }, dataR);
	setAnm({ OBJ_STATE::DEAD,DIR::LEFT }, dataL);
// 左右のアニメーションの登録-------------------------------------------

	_etype = ENEMY_TYPE::demon;
	_drawOffset_y = 64;
}
