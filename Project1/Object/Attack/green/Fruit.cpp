#include "Fruit.h"
#include "../../../Scene/SceneMng.h"
#include "../../../func/CheckHitStage.h"
#include "../../../Graphic/ImageMng.h"


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

	int tmpData = CheckHitStage()(static_cast<CHECK_DIR>(static_cast<int>(_state_dir.second) / 2), _pos, getHitOffset(), _stage);
	if (tmpData != NOTHIT)
	{
		_pos.x = tmpData - getHitOffset()[static_cast<int>(static_cast<int>(_state_dir.second) / 2)] * (static_cast<int>(_state_dir.second) - 1) * -1;
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
	std::uniform_int_distribution<unsigned int> _randDist(static_cast<int>(FRUIT_TYPE::WATERMELON),static_cast<int>(FRUIT_TYPE::MAX) - 1);

	_frType = static_cast<FRUIT_TYPE>(_randDist(lpSceneMng._rnd));


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
	attack.reserve(2);

	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -size, -size }, { size, size }, damage, 60, _target));
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -size, -size }, { size, size }, 0, -1, _target));

	setAttack("bubble", attack);

	_type = OBJ_TYPE::ATTACK;
	setHitOffset({ size,size,size,size });

	AddAttack("bubble");

	_radSpeed = ((_speed / (size * 2 * acos(-1.0f)) * (acos(-1.0f) * 2)));

	_tmpPos.y = _pos.y;
}

void Fruit::VelUpdate(void)
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
