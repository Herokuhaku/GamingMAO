#include "BubbleBlast.h"

BubbleBlast::BubbleBlast()
{
}

BubbleBlast::BubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_time = time;
	_stage = stage;

	_count = 0;

	setState({ OBJ_STATE::NORMAL, DIR::LEFT });

	std::vector<atkData> attack;
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 40,-40 }, { -40,40 }, 50, 30, target));
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 40,-40 }, { -40,40 }, 50, -1, target));
	setAttack("bubbleBlast", attack);

	_type = OBJ_TYPE::ATTACK;

	AddAttack("bubbleblast");
}

BubbleBlast::~BubbleBlast()
{
}

void BubbleBlast::Update(void)
{
	if (_count >= LIFE_TIME)
	{
		stopAttack();
		setState({ OBJ_STATE::DEAD, _state_dir.second });
		return;
	}

	_count++;
}

void BubbleBlast::IfHitAttack(void)
{
	// ‚È‚É‚à‚È‚µ
}
