#pragma once
#include "../Object/Object.h"

#define NOTHIT -20000

struct CheckHitStage
{
	int operator()(const CHECK_DIR& dir, const Vector2& pos, const std::array<int,4>& offset, int stage);
};

