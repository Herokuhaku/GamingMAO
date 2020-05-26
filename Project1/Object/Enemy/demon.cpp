#include "demon.h"
#include "../../Scene/SceneMng.h"

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
	AnmVec data;
	// ‰E-------------------------------------------
	for (int i = 0; i < 2; i++)
	{
		data.emplace_back(lpImageMng.getImage("demonR")[4 + i], 20 + i * 20);
	}
	setAnm({ OBJ_STATE::NORMAL,DIR::RIGHT }, data);

	for (int i = 0; i < 6; i++)
	{
		data.emplace_back(lpImageMng.getImage("demonR")[i], 20 + i * 20);
	}
	setAnm({ OBJ_STATE::WALK,DIR::RIGHT }, data);

	for (int i = 0; i < 4; i++)
	{
		data.emplace_back(lpImageMng.getImage("demonR")[16 + i], 20 + i * 20);
	}
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK,DIR::RIGHT }, data);

	for (int i = 0; i < 2; i++)
	{
		data.emplace_back(lpImageMng.getImage("demonR")[8 + i], 20 + i * 20);
	}
	data.emplace_back(-1,0);
	setAnm({ OBJ_STATE::DAMAGE,DIR::RIGHT }, data);

	for (int i = 0; i < 5; i++)
	{
		data.emplace_back(lpImageMng.getImage("demonR")[12 + i], 20 + i * 20);
	}
	data.emplace_back(-1,2828);
	setAnm({ OBJ_STATE::DEAD,DIR::RIGHT }, data);

	// ¶-------------------------------------------
	for (int i = 0; i < 2; i++)
	{
		data.emplace_back(lpImageMng.getImage("demonL")[4 + i], 20 + i * 20);
	}
	setAnm({ OBJ_STATE::NORMAL,DIR::LEFT }, data);

	for (int i = 0; i < 6; i++)
	{
		data.emplace_back(lpImageMng.getImage("demonL")[i], 20 + i * 20);
	}
	setAnm({ OBJ_STATE::WALK,DIR::LEFT }, data);

	for (int i = 0; i < 4; i++)
	{
		data.emplace_back(lpImageMng.getImage("demonL")[16 + i], 20 + i * 20);
	}
	data.emplace_back(-1, 0);
	setAnm({ OBJ_STATE::ATTACK,DIR::LEFT }, data);

	for (int i = 0; i < 2; i++)
	{
		data.emplace_back(lpImageMng.getImage("demonL")[8 + i], 20 + i * 20);
	}
	data.emplace_back(-1,0);
	setAnm({ OBJ_STATE::DAMAGE,DIR::LEFT }, data);

	for (int i = 0; i < 5; i++)
	{
		data.emplace_back(lpImageMng.getImage("demonL")[12 + i], 20 + i * 20);
	}
	data.emplace_back(-1, 2828);
	setAnm({ OBJ_STATE::DEAD,DIR::LEFT }, data);

	_etype = ENEMY_TYPE::s_dragon;

	_drawOffset_y + 30;
	_drawOffset_y + 30;
}
