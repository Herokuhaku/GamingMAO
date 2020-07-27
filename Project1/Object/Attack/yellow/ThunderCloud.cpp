#include "ThunderCloud.h"
#include "../AttackMng.h"
#include "../../../Graphic/ImageMng.h"
#include "../../../Manage/MapMng.h"


ThunderCloud::ThunderCloud(Vector2 pos, DIR dir, int speed, int count, int dur, TIME time, int stage, OBJ_TYPE target)
{
	_pos = pos;
	setState({ OBJ_STATE::NORMAL, dir });
	_speed = (static_cast<int>(dir) - 1) * speed;
	_countMax = count;
	_attackCount = 0;
	_attackDur = dur;
	_timer = 0;
	_time = time;
	_stage = stage;
	_target = target;
	_zOrder = 1;

	_tmpPos.x = static_cast<double>(_pos.x);

	Init();
}

ThunderCloud::~ThunderCloud()
{
}

void ThunderCloud::Update(void)
{
	_timer++;

	_pos.x += _speed;

	if (_timer >= _attackDur)
	{
		_timer = 0;
		_attackCount++;
		if (_attackCount > _countMax)
		{
			setState({ OBJ_STATE::DEAD, _state_dir.second });
			return;
		}

		int sPos = FindSF();
		if (sPos != -1)
		{
			lpAtkMng.MakeThunder(_pos, { _pos.x, sPos }, true, &_pos, 40, _time, _stage, _target);
		}
	}
}

void ThunderCloud::Init(void)
{
	AnmVec data;

	data.reserve(1);
	data.emplace_back( lpImageMng.getImage("cloud")[0], 1 );

	setAnm({ OBJ_STATE::NORMAL, _state_dir.second }, data);
	

}

int ThunderCloud::FindSF(void)
{
	int tmp = _pos.y;

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
