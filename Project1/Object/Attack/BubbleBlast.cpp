#include "BubbleBlast.h"

BubbleBlast::BubbleBlast()
{
}

BubbleBlast::BubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_time = time;
	_stage = stage;

	setState({ OBJ_STATE::DEAD, DIR::LEFT });

	std::vector<atkData> attack;
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 40,-40 }, { -40,40 }, 50, 10, target));
	setAttack("bubbleBlast", attack);
}

BubbleBlast::~BubbleBlast()
{
}
