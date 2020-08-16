#include "AttackMng.h"
#include "../../Manage/MapMng.h"
#include "red/FireBall.h"
#include "red/BombThrow.h"
#include "blue/Bubble.h"
#include "blue/BubbleBlast.h"
#include "green/Fruit.h"
#include "magenta/PoisonFog.h"
#include "cyan/IceWall.h"
#include "yellow/ThunderCloud.h"
#include "yellow/Thunder.h"
#include "white/HolyJudge.h"
#include "magenta/HealTree.h"
#include "yellow/Spark.h"

#include "../EnemyAttack/TrackingBall.h"

AttackMng* AttackMng::sInstance = nullptr;

void AttackMng::Update(void)
{
	auto itr = std::remove_if(_attackObj.begin(), _attackObj.end(), [](std::shared_ptr<Object> obj) {return obj->getState().first == OBJ_STATE::DEAD; });
	_attackObj.erase(itr, _attackObj.end());

	_canAddObj = false;

	for (const auto& data : _attackObj)
	{
		data->Update();
	}

	_canAddObj = true;

	for (auto& data : _tmpObj)
	{
		_attackObj.emplace_back(data);
	}

	_tmpObj.clear();
}

void AttackMng::Draw(void)
{
	for (const auto& data : _attackObj)
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
	if (_canAddObj)
	{
		_attackObj.emplace_back(new FireBall(pos, dir, vec, time, stage, target));
	}
	else
	{
		_tmpObj.emplace_back(new FireBall(pos, dir, vec, time, stage, target));
	}
}

void AttackMng::MakeBomb(Vector2 pos, DIR dir, int speed, double vel, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new BombThrow(pos, dir, speed, vel, time, stage, target));
	}
	else
	{
		_tmpObj.emplace_back(new BombThrow(pos, dir, speed, vel, time, stage, target));
	}
}

void AttackMng::MakeBubble(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new Bubble(pos, time, stage, target));
	}
	else
	{
		_tmpObj.emplace_back(new Bubble(pos, time, stage, target));
	}
}

void AttackMng::MakeBubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new BubbleBlast(pos, time, stage, target));
	}
	else
	{
		_tmpObj.emplace_back(new BubbleBlast(pos, time, stage, target));
	}
}

void AttackMng::MakeFruit(Vector2 pos, DIR dir, int speed, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new Fruit(pos, dir, speed, time, stage, target));
	}
	else
	{
		_tmpObj.emplace_back(new Fruit(pos, dir, speed, time, stage, target));
	}
}

void AttackMng::MakePoisonFog(Vector2 pos, int count, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new PoisonFog(pos, count, time, stage, target));
	}
	else
	{
		_tmpObj.emplace_back(new PoisonFog(pos, count, time, stage, target));
	}
}

void AttackMng::MakeHealTree(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new HealTree(pos, time, stage, target));
	}
	else
	{
		_tmpObj.emplace_back(new HealTree(pos, time, stage, target));
	}
}

void AttackMng::MakeIceWall(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new IceWall(pos, time, stage, target));
	}
	else
	{
		_tmpObj.emplace_back(new IceWall(pos, time, stage, target));
	}
}

void AttackMng::MakeThunderCloud(Vector2 pos, DIR dir, int speed, int count, int dur, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new ThunderCloud(pos, dir, speed, count, dur, time, stage, target));
	}
	else
	{
		_tmpObj.emplace_back(new ThunderCloud(pos, dir, speed, count, dur, time, stage, target));
	}
}

void AttackMng::MakeThunder(Vector2 pos1, Vector2 pos2, bool useRef, Vector2* refPos, int damage, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new Thunder(pos1, pos2, useRef, refPos, damage, time, stage, target));
	}
	else
	{
		_tmpObj.emplace_back(new Thunder(pos1, pos2, useRef, refPos, damage, time, stage, target));
	}
}

void AttackMng::MakeSpark(Vector2* pos, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new Spark(pos, time, stage, target));
	}
	else
	{
		_tmpObj.emplace_back(new Spark(pos, time, stage, target));
	}
}

int AttackMng::MakeHolyJudge(Vector2 pos, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new HolyJudge(pos, time, stage, target));

		return _attackObj.back()->getAnmEfk();
	}
	else
	{
		_tmpObj.emplace_back(new HolyJudge(pos, time, stage, target));

		return _tmpObj.back()->getAnmEfk();
	}
}

void AttackMng::MakeTrackingBall(Vector2 ePos, Vector2 pPos, TIME time, int stage, OBJ_TYPE target)
{
	if (_canAddObj)
	{
		_attackObj.emplace_back(new TrackingBall(ePos, pPos, time, stage, target));

	//	return _attackObj.back()->getAnmEfk();
	}
	else
	{
		_tmpObj.emplace_back(new TrackingBall(ePos, pPos, time, stage, target));

	//	return _tmpObj.back()->getAnmEfk();
	}
}

AttackMng::AttackMng()
{
	_canAddObj = true;
}

AttackMng::~AttackMng()
{

}
