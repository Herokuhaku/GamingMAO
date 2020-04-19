#include "s_dragon.h"
#include "../../Scene/SceneMng.h"

void s_dragon::Update(void)
{
	Enemy::Update();
}

//s_dragon::s_dragon(Vector2Template<int> pos, double rad, TIME time, int stage, OBJ_TYPE type, std::pair<OBJ_STATE, DIR> state_dir)
s_dragon::s_dragon()
	{
//		_pos = pos;
//	_rad = rad;
//	_time = TIME::NOW;
//	_stage = stage;
//	_zOrder = 10;
//	//_state_dir = { state_dir.first, state_dir.second };
	_state_dir = { OBJ_STATE::NORMAL,DIR::RIGHT };
//	_alive = true;
	Init();
//
}

s_dragon::~s_dragon()
{
}

void s_dragon::Init(void)
{
	AnmVec data;
	// ‰E-------------------------------------------
	for (int i = 0; i < 3; i++)
	{
		data.emplace_back(lpImageMng.getImage("s_dragonR")[4 + i], 20 + i * 20);
	}
	setAnm({ OBJ_STATE::NORMAL,DIR::RIGHT }, data);

	for (int i = 0; i < 4; i++)
	{
		data.emplace_back(lpImageMng.getImage("s_dragonR")[i], 20 + i * 20);
	}
	setAnm({ OBJ_STATE::WALK,DIR::RIGHT }, data);

	for (int i = 0; i < 3; i++)
	{
		data.emplace_back(lpImageMng.getImage("s_dragonR")[16 + i], 20 + i * 20);
	}
	data.emplace_back(-10, 0);
	setAnm({ OBJ_STATE::ATTACK,DIR::RIGHT }, data);

	for (int i = 0; i < 4; i++)
	{
		data.emplace_back(lpImageMng.getImage("s_dragonR")[12 + i], 20 + i * 20);
	}
	setAnm({ OBJ_STATE::DEAD,DIR::RIGHT }, data);

	// ¶-------------------------------------------
	for (int i = 0; i < 3; i++)
	{
		data.emplace_back(lpImageMng.getImage("s_dragonL")[4 + i], 20 + i * 20);
	}
	setAnm({ OBJ_STATE::NORMAL,DIR::LEFT }, data);

	for (int i = 0; i < 3; i++)
	{
		data.emplace_back(lpImageMng.getImage("s_dragonL")[16 + i], 20 + i * 20);
	}
	data.emplace_back(-10, 0);
	setAnm({ OBJ_STATE::ATTACK,DIR::LEFT }, data);

	for (int i = 0; i < 4; i++)
	{
		data.emplace_back(lpImageMng.getImage("s_dragonL")[12 + i], 20 + i * 20);
	}
	setAnm({ OBJ_STATE::DEAD,DIR::LEFT }, data);
}
