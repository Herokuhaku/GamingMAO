#include "ThunderAttack.h"
#include "../../Graphic/ImageMng.h"

ThunderAttack::ThunderAttack(Vector2 & ePos, DIR dir, TIME time, int stage, OBJ_TYPE target)
{
	_pos = { ePos.x + (60 * (dir == DIR::LEFT ? -1 : 1)), ePos.y - 200 };		// ‘„‚ÌoŒ»À•W
	_state_dir = { OBJ_STATE::NORMAL, dir };
	_time = time;
	_stage = stage;
	_target = target;
	_farstY = _pos.y;

	Init();
}

void ThunderAttack::Update(void)
{
	_pos.y+=6;
	if (_pos.y >= _farstY + 200)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
}

void ThunderAttack::IfHitAttack(std::shared_ptr<Object> target)
{
	target->SetStateEffect(new StateEffect(STATE_EFFECT_TYPE::PARALYSIS, 60));
}

bool ThunderAttack::Init(void)
{
	std::vector<atkData> attack;
	attack.reserve(1);

	//attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { _pos.x - 10, _pos.y - 10 }, { _pos.x + 10, _pos.y + 10 }, 30, 10, _target));
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, 120, 5, 60, _target));
	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0, 0 }, { 0, 0 }, 0, -1, _target));

	AnmVec data;
	data.reserve(30);
	for (int i = 0; i < 30; i++)
	{
		data.emplace_back(lpImageMng.getImage("fireball")[i], i + 1);
	}

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	setAttack("thunder", attack);
	AddAttack("thunder");
	return false;
}
