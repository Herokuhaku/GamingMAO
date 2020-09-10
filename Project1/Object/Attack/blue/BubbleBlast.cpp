#include "BubbleBlast.h"
#include "../../../Graphic/ImageMng.h"

namespace
{
	constexpr float ATTACK_RADIUS = 60.0f;
}

BubbleBlast::BubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_time = time;
	_stage = stage;

	_count = 0;

	setState({ OBJ_STATE::NORMAL, DIR::LEFT });

	std::vector<atkData> attack;
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, ATTACK_RADIUS, 25, 30, target));
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, ATTACK_RADIUS, 25, -1, target));
	setAttack("bubbleblast", attack);

	_type = OBJ_TYPE::ATTACK;

	AddAttack("bubbleblast");
}

BubbleBlast::~BubbleBlast()
{
}

void BubbleBlast::Update(void)
{
	setState({ OBJ_STATE::DEAD, DIR::LEFT });
}

void BubbleBlast::IfHitAttack(std::shared_ptr<Object> target)
{
	// ‚È‚É‚à‚È‚µ
}
