#include "Thunder.h"

Thunder::Thunder()
{
	Init();
}

Thunder::Thunder(Vector2 pos1, Vector2 pos2, int damage, TIME time, int stage, OBJ_TYPE target)
{
	if (pos2 == pos1)
	{
		setState({ OBJ_STATE::DEAD, DIR::LEFT });
		return;
	}

	if (pos2.y == pos1.y)
	{
		_rType = RAD_TYPE::HRZ;
		if (pos2.x > pos1.x)
		{
			_rad = 0.0;
		}
		else
		{
			_rad = acos(-1.0f);
		}
	}
	else if (pos2.x == pos1.x)
	{
		_rType = RAD_TYPE::VRT;
		if (pos2.y > pos1.y)
		{
			_rad = acos(-1.0f) / 2;
		}
		else
		{
			_rad = -(acos(-1.0f) / 2);
		}
	}
	else
	{
		_rType = RAD_TYPE::EX;
		_rad = atan2(pos2.y - pos1.y, pos2.x - pos1.x);
	}

	_pos = (pos2 - pos1) / 2;

	_stage = stage;

	_exRate = sqrt(pow(pos2.y - pos1.y, 2) + pow(pos2.x - pos1.x, 2)) / 256;

	AnmVec data;

	data.reserve(11);

	for (int i = 0; i < 11; i++)
	{
		data.emplace_back(lpImageMng.getImage("lightning")[i], 2 * (i + 1));
	}

	setState({ OBJ_STATE::NORMAL, DIR::LEFT });

	if (_rType != RAD_TYPE::EX || damage != 0)
	{
		_time = time;
		_damage = damage;
		_target = target;

		Init();
	}
}

Thunder::~Thunder()
{
}

void Thunder::Draw(void)
{
	if (!anmUpdate())
	{
		return;
	}

	lpImageMng.AddDraw({ _anmMap[_state_dir][_anmFlame].first, _pos.x, _pos.y - _drawOffset_y, _exRate, _rad, LAYER::CHAR, _zOrder, DX_BLENDMODE_ALPHA, 120 });
}

void Thunder::Init(void)
{
	std::vector<atkData> attack;
	attack.reserve(22);

	switch (_rType)
	{
	case RAD_TYPE::VRT:
		for (int i = 0; i < 22; i++)
		{
			attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -18, -64 }, { 18, 64 }, 0, 0, _target));
		}
		break;
	case RAD_TYPE::HRZ:
		for (int i = 0; i < 22; i++)
		{
			attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -64, -18 }, { 64, 18 }, 0, 0, _target));
		}
		break;
	default:
		setState({ OBJ_STATE::DEAD, _state_dir.second });
		break;
	}

	setAttack("thunder", attack);

	AddAttack("thunder");
}
