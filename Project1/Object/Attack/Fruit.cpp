#include "Fruit.h"
#include "../../Scene/SceneMng.h"
#include "../../func/CheckHitStage.h"

Fruit::Fruit()
{
}

Fruit::Fruit(Vector2 pos, DIR dir, int speed, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	setState({ OBJ_STATE::NORMAL, dir });
	_speed = (static_cast<int>(dir) - 1) * speed;
	_time = time;
	_stage = stage;
	_target = target;

	_rad = 0.0;
	_vel = 0.0;
	
	Init();
}

Fruit::~Fruit()
{
}

void Fruit::Update(void)
{
	_rad += _radSpeed;
	_pos.x += _speed;
	if (CheckHitStage()(static_cast<CHECK_DIR>(static_cast<int>(_state_dir.second) / 2), _pos, getHitOffset(), _stage) != NOTHIT)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}

	VelUpdate();
}

void Fruit::IfHitAttack(void)
{
	setState({ OBJ_STATE::DEAD, _state_dir.second });
}

void Fruit::Init(void)
{
	_frType = static_cast<FRUIT_TYPE>(lpSceneMng.GetRand(static_cast<int>(FRUIT_TYPE::MAX)));


	AnmVec data;
	data.reserve(1);

	data.emplace_back(lpImageMng.getImage("fruit")[static_cast<int>(_frType)], 1);

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	int size = 0;
	int damage = 0;
	switch (_frType)
	{
	case FRUIT_TYPE::WATERMELON:
		size = 30;
		damage = 50;
		break;
	case FRUIT_TYPE::APPLE:
		size = 22;
		damage = 30;
		break;
	case FRUIT_TYPE::ORANGE:
		size = 20;
		damage = 20;
		break;
	case FRUIT_TYPE::GRAPE:
		size = 12;
		damage = 10;
		break;
	default:
		return;
		break;
	}

	std::vector<atkData> attack;
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { size,-size }, { -size,size }, 0, 0, _target));
	setAttack("bubble", attack);

	_radSpeed = (static_cast<int>(_state_dir.second) - 1) * (_speed / (size * 2 * acos(-1.0f)) * (acos(-1.0f) * 2));

	_tmpPos.y = _pos.y;
}

void Fruit::VelUpdate(void)
{
	int tmpDown = CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, static_cast<int>(_tmpPos.y) + 1 }, getHitOffset(), _stage);
	if (tmpDown != NOTHIT)
	{
		_tmpPos.y = tmpDown - 1;
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

		tmpDown = CheckHitStage()(CHECK_DIR::DOWN, { _pos.x, static_cast<int>(_tmpPos.y) + _vel + 1 }, getHitOffset(), _stage);

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
