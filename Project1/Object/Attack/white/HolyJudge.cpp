#include "HolyJudge.h"


HolyJudge::HolyJudge(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	_pos.x = pos.x;
	_pos.y = FindSF(pos.y)/* - 540*/;
	_time = time;
	_stage = stage;
	_target = target;

	_count = 0;

	setState({ OBJ_STATE::NORMAL, DIR::LEFT });

	Init();
}

HolyJudge::~HolyJudge()
{
}

void HolyJudge::Update(void)
{
	_count++;
	if (_count >= LIFE_TIME)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
}

void HolyJudge::IfHitAttack(void)
{
}

void HolyJudge::Init(void)
{
	//AnmVec data;

	//data.reserve(15);

	//for (int i = 0; i < 15; i++)
	//{
	//	data.emplace_back(lpImageMng.getImage("magic_ring")[i], 3 * (i + 1));
	//}
	//setAnm({ OBJ_STATE::NORMAL, DIR::LEFT }, data);

	std::vector<atkData> attack;

	attack.reserve(220);

	for (int i = 0; i < 50; i++)
	{
		attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { -60, -1040 }, { 60, 0 }, 1, 0, _target));
	}
	for (int i = 50; i < 185; i++)
	{
		attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -60, -1040 }, { 60, 0 }, 1, 0, _target));
	}	for (int i = 185; i < 220; i++)
	{
		attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { -60, -1040 }, { 60, 0 }, 1, 0, _target));
	}

	setAttack("HolyJudgement", attack);

	AddAttack("HolyJudgement");

	_anmEfkHd = lpEffectMng.playEffect(lpEffectMng.getEffect("holy"), LIFE_TIME, &_pos.x, &_pos.y, 0, 0, &(_state_dir.second));
}

int HolyJudge::FindSF(int pos)
{
	int tmp = pos;

	while (!lpMapMng.getHitMap({ _pos.x, tmp }, _stage))
	{
		if (tmp > 3000)
		{
			return -1;
		}
		tmp += 16;
	}

	tmp = tmp - tmp % 16;

	return tmp;
}
