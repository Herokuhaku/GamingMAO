#pragma once
#include "../common/Vector2.h"
#include <array>

class Gimmick
{
public:
	Gimmick() = default;
	virtual ~Gimmick() = default;

	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
protected:
	Vector2Template<int> _pos;
	int _stage;
	std::array<int, 4> _hitBox;
	std::array<int, 4> _usableRange;
};

