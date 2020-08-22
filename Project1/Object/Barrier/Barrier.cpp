#include "Barrier.h"
#include "../Object.h"
#include "../../Graphic/ImageMng.h"

namespace
{
	constexpr int ANM_SPEED = 2;
	constexpr int ANM_COUNT = 8;

	constexpr int ACTIVE_DURATION = 100;
}

Barrier::Barrier(std::weak_ptr<Object> owner, COLOR color, const Vector2& offset, const std::string& imageKey)
	:_owner(owner), _color(color), _offset(offset), _imageKey(imageKey)
{
	_hitBox = { 19, 0, 25, 25 };
	_timer = 0;
	_update = &Barrier::ExpandUpdate;
	_draw = &Barrier::DeactiveDraw;
}

void Barrier::Update(void)
{
	(this->*_update)();
}

void Barrier::Draw(void)
{
	(this->*_draw)();
}

bool Barrier::IsActive(void)
{
	return _active;
}

bool Barrier::IsDelete(void)
{
	return _delete;
}

bool Barrier::IsDead(void)
{
	return _owner.expired();
}

void Barrier::ExpandUpdate(void)
{
	_timer++;
	if (_timer >= ANM_SPEED * (ANM_COUNT - 1))
	{
		_timer = 0;
		_update = &Barrier::ActiveUpdate;
		_draw = &Barrier::ActiveDraw;
		_active = true;
	}
}

void Barrier::ActiveUpdate(void)
{
	_timer++;
	if (_timer > ACTIVE_DURATION)
	{
		_timer = ANM_SPEED * (ANM_COUNT - 1) - 1;
		_update = &Barrier::ReduceUpdate;
		_draw = &Barrier::DeactiveDraw;
		_active = false;
	}
}

void Barrier::ReduceUpdate(void)
{
	_timer--;
	if (_timer <= 0)
	{
		_delete = true;
	}
}

void Barrier::DeactiveDraw(void)
{
	if (IsDead())
	{
		return;
	}
	Vector2 pos = GetPos();
	lpImageMng.AddDraw({ lpImageMng.getImage(_imageKey)[ANM_COUNT * (static_cast<int>(_owner.lock()->getState().second) / 2) + _timer / ANM_SPEED], pos.x, pos.y, 1.0, 0.0, LAYER::CHAR, 100, DX_BLENDMODE_NOBLEND, 0 });
}

void Barrier::ActiveDraw(void)
{
	if (IsDead())
	{
		return;
	}
	Vector2 pos = GetPos();
	lpImageMng.AddDraw({ lpImageMng.getImage(_imageKey)[ANM_COUNT * (static_cast<int>(_owner.lock()->getState().second) / 2) + ANM_COUNT - 1], pos.x, pos.y, 1.0, 0.0, LAYER::CHAR, 100, DX_BLENDMODE_NOBLEND, 0 });
}

Vector2 Barrier::GetPos(void)
{
	if (IsDead())
	{
		return Vector2();
	}
	Vector2 pos = _owner.lock()->getPos();
	Vector2 offset;
	_owner.lock()->getState().second == DIR::LEFT ? offset = { _offset.x * -1, _offset.y } : offset = _offset;
	return Vector2(pos + offset);
}

std::array<int, 4> Barrier::GetHitOffset(void)
{
	if (IsDead())
	{
		return { 0,0,0,0 };
	}

	std::array<int, 4> rtn = _hitBox;
	if (_owner.lock()->getState().second == DIR::RIGHT)
	{
		rtn[0] = _hitBox[1];
		rtn[1] = _hitBox[0];
	}

	return rtn;
}

TIME Barrier::GetTimeLine(void)
{
	if (IsDead())
	{
		return TIME::FTR;
	}
	return _owner.lock()->getTimeLine();
}

int Barrier::GetStage(void)
{
	if (IsDead())
	{
		return -1;
	}
	return _owner.lock()->getStage();
}

OBJ_TYPE Barrier::GetOwnerType(void)
{
	if (IsDead())
	{
		return OBJ_TYPE::MAX;
	}
	return _owner.lock()->getObjType();
}
