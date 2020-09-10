#include "SpearAttack.h"
#include "../../Graphic/ImageMng.h"
#include "../../Scene/SceneMng.h"
#include "../Attack/AttackMng.h"


SpearAttack::SpearAttack(Vector2 & ePos, DIR dir, TIME time, int stage, OBJ_TYPE target)
{
	_pos = { ePos.x + (60 * (dir == DIR::LEFT ? -1 : 1)), ePos.y };		// ëÑÇÃèoåªç¿ïW
	_state_dir = { OBJ_STATE::NORMAL, dir };
	_time = time;
	_stage = stage;
	_target = target;
	_farstY = _pos.y;

	Init();
}

SpearAttack::~SpearAttack()
{
}

void SpearAttack::Update(void)
{
	_pos.y-=3;
	if (_pos.y <= _farstY - 100)
	{
		setState({ OBJ_STATE::DEAD, _state_dir.second });
	}
}

void SpearAttack::Draw(void)
{
	Object::Draw();
}

void SpearAttack::IfHitAttack(std::shared_ptr<Object> target)
{
	setState({ OBJ_STATE::DEAD, _state_dir.second });
	target->MovePos({ (20 * ((target->getPos().x < _pos.x) ? -1 : 1)), -15 });
}

bool SpearAttack::Init(void)
{
	std::vector<atkData> attack;
	attack.reserve(1);

	//attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { _pos.x - 10, _pos.y - 10 }, { _pos.x + 10, _pos.y + 10 }, 30, 10, _target));
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, 50, 1, 10, _target));
//	attack.emplace_back(atkData(false, OBJ_TYPE::ATTACK, { 0, 0 }, { 0, 0 }, 0, -1, _target));

	AnmVec data;
	data.reserve(30);
	for (int i = 0; i < 30; i++)
	{
		data.emplace_back(lpImageMng.getImage("fireball")[i], i + 1);
	}

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);

	setAttack("spear", attack);
	AddAttack("spear");
	return false;
}
