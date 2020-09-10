#include "DamageDisplay.h"
#include "../Graphic/StringAddDraw.h"
#include "../Scene/SceneMng.h"
#include <algorithm>
#include "MapMng.h"
#include "../common/algo.h"

namespace
{
	constexpr int DRAW_DURATION = 32;
	constexpr int FADEOUT_DURATION = 5;
}

DamageDisplay& DamageDisplay::GetInstance()
{
	static DamageDisplay d;
	return d;
}

void DamageDisplay::Draw(void)
{
	Vector2D cpos = lpSceneMng.GetcPos();
	int cx = static_cast<int>(cpos.x) - lpSceneMng.ScreenSize.x / 2;
	int cy = static_cast<int>(cpos.y) - lpSceneMng.ScreenSize.y / 2;
	for (auto& d : _damage)
	{
		if (d->_stage == lpMapMng.GetnowStage())
		{
			lpStrAdd.AddStringDraw(std::to_string(d->_damage).c_str(), "SQUARE_BIG", d->_pos.x - cx, d->_pos.y - cy - d->_timer, d->_color, DRAW_TO_CENTER, DX_BLENDMODE_ALPHA,static_cast<int>(255.0f *  algo::Clamp(static_cast<float>(DRAW_DURATION - d->_timer) / static_cast<float>(FADEOUT_DURATION), 0.0f, 1.0f)));
		}
		d->_timer++;
		if (d->_timer >= DRAW_DURATION)
		{
			d->_delete = true;
		}
	}

	std::deque<std::unique_ptr<DamageInfo>>::iterator it = std::remove_if(_damage.begin(), _damage.end(), [](std::unique_ptr<DamageInfo>& d) { return d->_delete == true; });
	_damage.erase(it, _damage.end());
}

void DamageDisplay::AddDamage(DamageInfo * dInfo)
{
	_damage.emplace_back(dInfo);
}
