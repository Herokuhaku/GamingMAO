#include "Gimmick.h"

Gimmick::Gimmick(const Vector2Template<int>& pos, int stage) :_pos(pos), _stage(stage), _hitBox(), _usableRange()
{
}

bool Gimmick::isDeleted(void)
{
	return _deleted;
}

const Vector2Template<int>& Gimmick::GetPos(void) const
{
	return _pos;
}

const std::array<int, 4>& Gimmick::GetHitBox(void) const
{
	return _hitBox;
}

const std::array<int, 4>& Gimmick::GetUsable(void) const
{
	return _usableRange;
}
