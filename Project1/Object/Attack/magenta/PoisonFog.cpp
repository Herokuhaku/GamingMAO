#include "PoisonFog.h"
#include "../../../Graphic/ImageMng.h"


PoisonFog::PoisonFog(Vector2 pos, int count, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	_time = time;
	_stage = stage;
	_target = target;
	_lifeTime = count;

	_count = 0;


	setState({ OBJ_STATE::JUMP, DIR::LEFT });

	Init();
}

PoisonFog::~PoisonFog()
{

}

void PoisonFog::Update(void)
{
	if (!_alive)
	{
		_state_dir.first = OBJ_STATE::DEAD;
		return;
	}

	if (_state_dir.first == OBJ_STATE::NORMAL)
	{
		if (_count == 0)
		{
			AddAttack("poison_mist");
		}

		if (_count < _lifeTime)
		{
			_count++;
		}
		else
		{
			setState({ OBJ_STATE::FALL, _state_dir.second });
			stopAttack();
		}
	}
}

void PoisonFog::IfHitAttack(void)
{
	// ‚È‚É‚à‚µ‚È‚¢
}

void PoisonFog::Init(void)
{
	AnmVec data;

	data.reserve(6);

	data.emplace_back(lpImageMng.getImage("poison_mist")[0], 5);
	data.emplace_back(lpImageMng.getImage("poison_mist")[6], 10);
	data.emplace_back(lpImageMng.getImage("poison_mist")[5], 15);
	data.emplace_back(lpImageMng.getImage("poison_mist")[4], 20);
	data.emplace_back(-1, 0);

	setAnm({ OBJ_STATE::JUMP, _state_dir.second }, data);

	data.emplace_back(lpImageMng.getImage("poison_mist")[3], 15);
	data.emplace_back(lpImageMng.getImage("poison_mist")[2], 30);


	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);
	
	data.emplace_back(lpImageMng.getImage("poison_mist")[3], 5);
	data.emplace_back(lpImageMng.getImage("poison_mist")[4], 10);
	data.emplace_back(lpImageMng.getImage("poison_mist")[5], 15);
	data.emplace_back(lpImageMng.getImage("poison_mist")[6], 20);
	data.emplace_back(lpImageMng.getImage("poison_mist")[7], 25);
	data.emplace_back(-1, -1);

	setAnm({ OBJ_STATE::FALL, _state_dir.second }, data);

	std::vector<atkData> attack;
	attack.reserve(1);

	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { -150, -60 }, { 150, 60 }, 1, 6, _target));
	attack.emplace_back(atkData(true, OBJ_TYPE::ATTACK, { 0, 0 }, { 0, 0 }, 0, -1, _target));

	setAttack("poison_mist", attack);

	_type = OBJ_TYPE::ATTACK;

}
