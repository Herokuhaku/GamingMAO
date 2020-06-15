#include "IceWall.h"


IceWall::IceWall(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_time = time;
	_stage = stage;
	_target = target;

	setState({ OBJ_STATE::NORMAL, DIR::LEFT });

	Init();
}

IceWall::~IceWall()
{
}

void IceWall::Update(void)
{
	if (!_alive)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
}

void IceWall::IfHitAttack(void)
{
}

void IceWall::Init(void)
{
	AnmVec data;

	data.reserve(8);

	for (int i = 0; i < 8; i++)
	{
		data.emplace_back(lpImageMng.getImage("ice_wall")[i], 5 * (i + 1));
	}
	data.emplace_back(-1, -1);

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	std::vector<atkData> attack;

	attack.reserve(40);

	for (int i = 0; i < 5; i++)
	{
		attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { -160, -60 }, { 160, 60 }, 30, 15, _target));
	}
	for (int i = 5; i < 20; i++)
	{
		attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -160, -60 }, { 160, 60 }, 30, 15, _target));
	}	for (int i = 20; i < 40; i++)
	{
		attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { -160, -60 }, { 160, 60 }, 30, 15, _target));
	}

	setAttack("IceWall", attack);

	AddAttack("IceWall");

	_type = OBJ_TYPE::ATTACK;
}
