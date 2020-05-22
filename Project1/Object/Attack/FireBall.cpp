#include "FireBall.h"

FireBall::FireBall()
{

}

FireBall::FireBall(Vector2 pos, DIR dir, int speed, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_state_dir = { OBJ_STATE::NORMAL, dir };
	_speed = static_cast<int>(dir) * speed;
	_time = time;
	_stage = stage;
	_target = target;

	Init();
}

FireBall::~FireBall()
{

}

void FireBall::Update(void)
{
	_pos.x += _speed;
	if (CheckHitStage()(static_cast<CHECK_DIR>(static_cast<int>(_state_dir.second) / 2), _pos, getHitOffset(), _stage) != NOTHIT)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
	
}

void FireBall::IfHitAttack(void)
{
	setState({ OBJ_STATE::DEAD, _state_dir.second });
}

void FireBall::Init(void)
{
	AnmVec data;
	data.reserve(30);

	for (int i = 0; i < 30; i++)
	{
		data.emplace_back(lpImageMng.getImage("fireball")[i], i + 1);
	}

	std::vector<atkData> attack;
	attack.reserve(31);
	for (int i = 0; i < 30; i++)
	{
		attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 42,35 }, { 16,55 }, 10, 10, _target));
	}
	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0,0 }, { 0,0 }, 0, 0, _target));

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);
	 
	_type = OBJ_TYPE::ATTACK;
	setHitOffset({ 0,20,6,14 });
}
