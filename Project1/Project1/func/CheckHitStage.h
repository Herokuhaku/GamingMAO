#pragma once
#include "../Object/Object.h"
#include "../MapMng.h"

struct CheckHitStage
{
	bool operator()(const CHECK_DIR& dir, const Vector2& pos, const std::array<int,4>& offset);
};

