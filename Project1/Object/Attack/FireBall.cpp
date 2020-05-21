#include "FireBall.h"

FireBall::FireBall()
{

}

FireBall::FireBall(Vector2 pos, DIR dir, int speed, TIME time, int stage)
{
	_pos = pos;
	_state_dir = { OBJ_STATE::NORMAL, dir };
	_speed = speed;
	_time = time;
	_stage = stage;

	Init();
}

FireBall::~FireBall()
{

}

void FireBall::Update(void)
{
}

void FireBall::Init(void)
{
	AnmVec data;
	data.reserve(30);

	for (int i = 0; i < 30; i++)
	{
		data.emplace_back(lpImageMng.getImage("fireball")[i], i + 1);
	}
	
	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	_type = OBJ_TYPE::ATTACK;
	setHitOffset({ 0,20,6,14 });
}
