#include "GimmickMng.h"
#include "Gimmick.h"
#include <algorithm>
#include "../Object/Item.h"
#include "../Manage/MapMng.h"

std::vector<std::shared_ptr<Gimmick>> GimmickMng::_gimmickList;

void GimmickMng::Update(void)
{
	for (const auto& gm : _gimmickList)
	{
		gm->Update();
	}

	auto it = std::remove_if(_gimmickList.begin(), _gimmickList.end(), [](const std::shared_ptr<Gimmick>& gim) { return gim->isDeleted(); });
	_gimmickList.erase(it, _gimmickList.end());
}

void GimmickMng::Draw(void)
{
	for (const auto& gm : _gimmickList)
	{
		if (lpMapMng.GetnowStage() == gm->GetStage())
		{
			gm->Draw();
		}
	}
}

void GimmickMng::AddGimmick(Gimmick * gimmick)
{
	_gimmickList.emplace_back(gimmick);
}

const std::vector<std::shared_ptr<Gimmick>>& GimmickMng::GetGimmicks(void)
{
	return _gimmickList;
}

void GimmickMng::CheckUsableRange(Vector2Template<int> pos, int stage, const ItemSave& item)
{
	if (item.itemtype == ITEM_TYPE::NON)
	{
		return;
	}
	std::array<int, 4> gmBox;
	Vector2Template<int> gmPos;
	for (const auto& gm : _gimmickList)
	{
		if (gm->GetStage() != stage)
		{
			continue;
		}
		gmBox = gm->GetUsable();
		gmPos = gm->GetPos();
		if (pos.x >= gmBox[static_cast<int>(CHECK_DIR::LEFT)] + gmPos.x &&
			pos.x <= gmBox[static_cast<int>(CHECK_DIR::RIGHT)] + gmPos.x &&
			pos.y >= gmBox[static_cast<int>(CHECK_DIR::UP)] + gmPos.y &&
			pos.y <= gmBox[static_cast<int>(CHECK_DIR::DOWN)] + gmPos.y)
		{
			gm->Action(item);
		}
	}
}

GimmickMng::GimmickMng()
{

}