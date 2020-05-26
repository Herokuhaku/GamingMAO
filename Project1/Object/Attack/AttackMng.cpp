#include "AttackMng.h"
#include "red/FireBall.h"
#include "blue/Bubble.h"
#include "blue/BubbleBlast.h"

AttackMng* AttackMng::sInstance = nullptr;

void AttackMng::Update(void)
{
	auto itr = std::remove_if(_attackObj.begin(), _attackObj.end(), [](std::shared_ptr<Object> obj) {return obj->getState().first == OBJ_STATE::DEAD; });
	_attackObj.erase(itr, _attackObj.end());

	for (auto data : _attackObj)
	{
		data->Update();
	}
}

void AttackMng::Draw(void)
{
	for (auto data : _attackObj)
	{
		if (data->getStage() == lpMapMng.GetnowStage())
		{
			data->Draw();
			data->attackUpdate();
		}
	}
}

std::vector<std::shared_ptr<Object>> AttackMng::GetAttackObjList(void)
{
	return _attackObj;
}

void AttackMng::MakeFireBall(Vector2 pos, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target)
{
	_attackObj.emplace_back(new FireBall(pos, dir, vec, time, stage, target));
}

void AttackMng::MakeBubble(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	_attackObj.emplace_back(new Bubble(pos, time, stage, target));
}

void AttackMng::MakeBubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	_attackObj.emplace_back(new BubbleBlast(pos, time, stage, target));
}

AttackMng::AttackMng()
{

}

AttackMng::~AttackMng()
{

}
