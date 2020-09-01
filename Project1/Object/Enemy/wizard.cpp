#include "wizard.h"
#include "../../Scene/SceneMng.h"
#include "../../Graphic/ImageMng.h"
#include "../../Manage/MapMng.h"

void wizard::Update(void)
{
	Enemy::Update();
}

//s_dragon::s_dragon(Vector2Template<int> pos, double rad, TIME time, int stage, OBJ_TYPE type, std::pair<OBJ_STATE, DIR> state_dir)
wizard::wizard(Vector2 pos, int stage)
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

wizard::wizard(Vector2 pos, int stage, int pPos, bool flag)
{
	_pos = pos;
	_stage = stage;
	_etype = ENEMY_TYPE::s_dragon;
	_pPos = pPos;
	_state_dir = { OBJ_STATE::NORMAL,DIR::RIGHT };
	setHP(100);
	setHitOffset({ 55, 55, 100, 0 });
	_exRate = 3.0;
	_stateEffectExRate = 2.0;

	_rangeSF = 300;
	_rangeA = 200;

	if (flag)
	{
		while (!lpMapMng.getHitMap(_pos, _stage))
		{
			_pos.y += 1;
		}
	}
	Init();
}

wizard::~wizard()
{
}

void wizard::Init(void)
{
	AnmVec data;
	int animCnt = 10;
	// ‰E++-----------------------------------------
	for (int i = 0; i < 10; i++)
	{
		data.emplace_back(lpImageMng.getImage("wizardR")[19 - i], animCnt + i * animCnt);
	}
	setAnm({ OBJ_STATE::NORMAL,DIR::RIGHT }, data);

	for (int i = 0; i < 5; i++)
	{
		data.emplace_back(lpImageMng.getImage("wizardR")[9 - i], animCnt + i * animCnt);
	}
	setAnm({ OBJ_STATE::WALK,DIR::RIGHT }, data);

	animCnt = 5;
	for (int i = 0; i < 10; i++)
	{
		data.emplace_back(lpImageMng.getImage("wizardR")[49 - i], animCnt + i * animCnt);
	}
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK,DIR::RIGHT }, data);
	animCnt = 10;

	for (int i = 0; i < 4; i++)
	{
		data.emplace_back(lpImageMng.getImage("wizardR")[29 - i], animCnt + i * animCnt);
	}
	data.emplace_back(-1,0);
	setAnm({ OBJ_STATE::DAMAGE,DIR::RIGHT }, data);

	for (int i = 0; i < 10; i++)
	{
		data.emplace_back(lpImageMng.getImage("wizardR")[39 - i], animCnt + i * animCnt);
	}
	data.emplace_back(-1,2828);
	setAnm({ OBJ_STATE::DEAD,DIR::RIGHT }, data);

	// ¶++-----------------------------------------
	for (int i = 0; i < 10; i++)
	{
		data.emplace_back(lpImageMng.getImage("wizardL")[10 + i], animCnt + i * animCnt);
	}
	setAnm({ OBJ_STATE::NORMAL,DIR::LEFT }, data);

	for (int i = 0; i < 6; i++)
	{
		data.emplace_back(lpImageMng.getImage("wizardL")[i], animCnt + i * animCnt);
	}
	setAnm({ OBJ_STATE::WALK,DIR::LEFT }, data);

	animCnt = 5;
	for (int i = 0; i < 10; i++)
	{	
		data.emplace_back(lpImageMng.getImage("wizardL")[40 + i], animCnt + i * animCnt);
	}
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK,DIR::LEFT }, data);
	animCnt = 10;

	for (int i = 0; i < 4; i++)
	{
		data.emplace_back(lpImageMng.getImage("wizardL")[20 + i], animCnt + i * animCnt);
	}
	data.emplace_back(-1,0);
	setAnm({ OBJ_STATE::DAMAGE,DIR::LEFT }, data);

	for (int i = 0; i < 10; i++)
	{
		data.emplace_back(lpImageMng.getImage("wizardL")[30 + i], animCnt + i * animCnt);
	}
	data.emplace_back(-1, 2828);
	setAnm({ OBJ_STATE::DEAD,DIR::LEFT }, data);

	_etype = ENEMY_TYPE::s_dragon;
	_drawOffset_y = 80 * (int)_exRate / 2;
}
