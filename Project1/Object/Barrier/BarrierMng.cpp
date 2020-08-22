#include "BarrierMng.h"
#include <cassert>
#include <cmath>
#include <algorithm>
#include "../../Graphic/ImageMng.h"
#include "../../Manage/COLOR.h"
#include "../../Object/Object.h"
#include "Barrier.h"
#include "../../Scene/GameScene.h"

namespace
{
	const std::string imageKey[3] = { "shield_red", "shield_green", "shield_blue" };
}

BarrierMng::BarrierMng(GameScene* gs):_gamescene(gs)
{
	lpImageMng.getImage("image/Attack/shield_red.png", imageKey[0], 50, 80, 8, 2);
	lpImageMng.getImage("image/Attack/shield_green.png", imageKey[1], 50, 80, 8, 2);
	lpImageMng.getImage("image/Attack/shield_blue.png", imageKey[2], 50, 80, 8, 2);
}

void BarrierMng::Update(void)
{
	for (const auto& b : _barriers)
	{
		b->Update();
	}
	auto it = std::remove_if(_barriers.begin(), _barriers.end(), [](std::shared_ptr<Barrier>& br) { return br->IsDelete() || br->IsDead(); });
	_barriers.erase(it, _barriers.end());
}

void BarrierMng::Draw(void)
{
	for (const auto& b : _barriers)
	{
		b->Draw();
	}
}

const std::vector<std::shared_ptr<Barrier>>& BarrierMng::GetBarrier(void)
{
	return _barriers;
}

void BarrierMng::MakeBarrier(Object* owner, COLOR color, const Vector2& offset)
{
	std::string key;
	std::shared_ptr<Object> obj;

	assert(color == COLOR::RED || color == COLOR::GREEN || color == COLOR::BLUE);

	key = imageKey[static_cast<int>(log2(static_cast<int>(color)))];

	obj = _gamescene->FindObject(owner);
	if (obj == nullptr)
	{
		return;
	}
	
	_barriers.emplace_back(new Barrier(obj, color, offset, key));
}
