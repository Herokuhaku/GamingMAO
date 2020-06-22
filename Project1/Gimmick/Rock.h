#pragma once
#include "Gimmick.h"

class Rock :
	public Gimmick
{
public:
	Rock() = delete;
	Rock(const Vector2& pos, const int& stage);
	~Rock();


private:
};

