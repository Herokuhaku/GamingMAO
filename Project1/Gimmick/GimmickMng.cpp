#include "GimmickMng.h"
#include "Gimmick.h"
#include <algorithm>

std::vector<std::shared_ptr<Gimmick>> GimmickMng::_gimmickList;

void GimmickMng::Update(void)
{
	for (const auto& data : _gimmickList)
	{
		data->Update();
	}

	auto it = std::remove_if(_gimmickList.begin(), _gimmickList.end(), [](const std::shared_ptr<Gimmick>& gim) { return gim->isDeleted(); });
	_gimmickList.erase(it, _gimmickList.end());
}

void GimmickMng::Draw(void)
{
	for (const auto& data : _gimmickList)
	{
		data->Draw();
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

GimmickMng::GimmickMng()
{

}