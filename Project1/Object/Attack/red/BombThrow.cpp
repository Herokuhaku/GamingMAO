#include "BombThrow.h"
#include "../../../func/CheckHitStage.h"
#include "../../../Graphic/ImageMng.h"


BombThrow::BombThrow(Vector2 pos, DIR dir, int speed, double vel, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_speed = (static_cast<int>(dir) - 1) * speed;
	_vel = vel;
	_time = time;
	_stage = stage;
	_rad = 0.0;

	setState({ OBJ_STATE::NORMAL, dir });

	Init();
}

BombThrow::~BombThrow()
{
}

void BombThrow::Update(void)
{
	_rad += (static_cast<int>(_state_dir.second) - 1) * RAD_VEL;
}

void BombThrow::IfHitAttack(void)
{
}

void BombThrow::Init(void)
{
	AnmVec data;

	data.emplace_back(lpImageMng.getImage("bomb")[0], 5);
	data.emplace_back(lpImageMng.getImage("bomb")[1], 10);

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	std::vector<atkData> attack;


}

void BombThrow::VelUpdate(void)
{
	int tmpDown = CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, static_cast<int>(_tmpPos.y) + getHitOffset()[static_cast<int>(CHECK_DIR::DOWN)] + 1 }, getHitOffset(), _stage);
	if (tmpDown != NOTHIT)
	{
		_tmpPos.y = tmpDown - getHitOffset()[static_cast<int>(CHECK_DIR::DOWN)] - 1;
		_vel = 0.0;
	}
	else
	{
		if (_vel + G_ACC > ACC_MAX)
		{
			_vel = ACC_MAX;
		}
		else
		{
			_vel += G_ACC;
		}

		tmpDown = CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, static_cast<int>(_tmpPos.y + _vel) + 1 }, getHitOffset(), _stage);

		if (tmpDown != NOTHIT)
		{
			_tmpPos.y = tmpDown - 1;
			_vel = 0.0;
		}
		else
		{
			_tmpPos.y += _vel;
		}
	}

	_pos.y = _tmpPos.y;
}
