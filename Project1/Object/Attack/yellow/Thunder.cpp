#include "Thunder.h"
#include "../../../Graphic/ImageMng.h"
#include "../../../Audio/AudioContainer.h"

namespace
{
	AudioContainer _audio;
}

Thunder::Thunder(Vector2 pos1, Vector2 pos2, bool useRef, Vector2* refPos, int damage, TIME time, int stage, OBJ_TYPE target)
{
	_exRate = sqrt(pow(pos2.y + 40 - pos1.y, 2) + pow(pos2.x - pos1.x, 2)) / 240;
	pos2.y += 40;

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
			_rad = -acos(1.0f) / 2.0;
		}
		else
		{
			_rad = acos(-1.0f) / 2.0;
		}
	}
	else if (pos2.x == pos1.x)
	{
		_rType = RAD_TYPE::VRT;
		if (pos2.y > pos1.y)
		{
			_rad = 0.0;
		}
		else
		{
			_rad = acos(-1.0f);
		}
	}
	else
	{
		_rType = RAD_TYPE::EX;
		_rad = atan2(pos2.y - pos1.y, pos2.x - pos1.x);
	}

	_pos = pos1 + (pos2 - pos1) / 2;

	if (useRef)
	{
		_refPos = refPos;
		_offset = _pos - (*refPos);
	}
	else
	{
		_refPos = &_pos;
		_offset = { 0,0 };
	}

	_stage = stage;

	AnmVec data;

	data.reserve(9);

	for (int i = 0; i < 8; i++)
	{
		data.emplace_back(lpImageMng.getImage("lightning")[i], 2 * (i + 1));
	}
	data.emplace_back(-1, -1);

	setAnm({ OBJ_STATE::NORMAL, DIR::LEFT }, data);

	setState({ OBJ_STATE::NORMAL, DIR::LEFT });

	if (_rType != RAD_TYPE::EX || damage != 0)
	{
		_time = time;
		_damage = damage;
		_target = target;

		Init();
	}

	_audio.LoadSound("sound/magic/thunder.wav", "thunder", 10);
	_audio.ChangeVolume("thunder", 180);
	PlaySoundMem(_audio.GetSound("thunder"), DX_PLAYTYPE_BACK, true);
}

Thunder::~Thunder()
{
}

void Thunder::Update(void)
{
	_pos = (*_refPos) + _offset;
}

void Thunder::Draw(void)
{
	if (!anmUpdate())
	{
		return;
	}

	lpImageMng.AddDraw({ _anmMap[_state_dir][_anmFlame].first, _pos.x, _pos.y - _drawOffset_y, _exRate, _rad, LAYER::CHAR, _zOrder, DX_BLENDMODE_NOBLEND, 0, true });
}

void Thunder::IfHitAttack(std::shared_ptr<Object> target)
{
	if (target != nullptr)
	{
		target->SetStateEffect(new StateEffect(STATE_EFFECT_TYPE::PARALYSIS, 60));
	}
}

void Thunder::Init(void)
{
	std::vector<atkData> attack;
	attack.reserve(22);

	Vector2 attackSize = { static_cast<int>(18.0 * _exRate), static_cast<int>(64.0 * _exRate) };

	switch (_rType)
	{
	case RAD_TYPE::VRT:
		for (int i = 0; i < 22; i++)
		{
			attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -attackSize.x, -attackSize.y }, { attackSize.x, attackSize.y }, 40, 22, _target));
		}
		break;
	case RAD_TYPE::HRZ:
		for (int i = 0; i < 22; i++)
		{
			attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -attackSize.y, -attackSize.x }, { attackSize.y, attackSize.x }, 40, 2, _target));
		}
		break;
	default:
		setState({ OBJ_STATE::DEAD, _state_dir.second });
		break;
	}

	setAttack("thunder", attack);

	AddAttack("thunder");
}
