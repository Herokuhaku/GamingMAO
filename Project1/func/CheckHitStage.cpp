#include "CheckHitStage.h"
#include "../Gimmick/Gimmick.h"
#include "../Gimmick/GimmickMng.h"
#include <algorithm>
#include "../Manage/MapMng.h"


int CheckHitStage::operator()(const CHECK_DIR & dir, const Vector2 & pos, const std::array<int, 4>& offset, int stage)
{
	std::vector<std::shared_ptr<Gimmick>> gimmick = GimmickMng::GetGimmicks();
	int width = offset[static_cast<int>(CHECK_DIR::LEFT)] + offset[static_cast<int>(CHECK_DIR::RIGHT)];
	int height = offset[static_cast<int>(CHECK_DIR::UP)] + offset[static_cast<int>(CHECK_DIR::DOWN)] - 1;
	int rtnPos = NOTHIT;

	int top = pos.y - offset[static_cast<int>(CHECK_DIR::UP)];
	int bottom = pos.y + offset[static_cast<int>(CHECK_DIR::DOWN)];
	int left = pos.x - offset[static_cast<int>(CHECK_DIR::LEFT)];
	int right = pos.x + offset[static_cast<int>(CHECK_DIR::RIGHT)];

	Vector2Template<int> gmPos;
	std::array<int, 4> gmBox;
	switch (dir)
	{
	case CHECK_DIR::LEFT:
		for (int i = 0; i < height; i += CHIP_SIZE)
		{
			if (lpMapMng.getHitMap({ left, top + i }, stage))
			{
				if (rtnPos > left + (CHIP_SIZE - left % CHIP_SIZE) + 1 || rtnPos == NOTHIT)
				{
					rtnPos = left + (CHIP_SIZE - left % CHIP_SIZE) + 1;
				}
			}
		}

		if (lpMapMng.getHitMap({ left, bottom - 1 }, stage))
		{
			if (rtnPos > left + (CHIP_SIZE - left % CHIP_SIZE)  + 1|| rtnPos == NOTHIT)
			{
				rtnPos = left + (CHIP_SIZE - left % CHIP_SIZE) + 1;
			}
		}
		for (auto& gm : gimmick)
		{
			gmPos = gm->GetPos();
			gmBox = gm->GetHitBox();
			if (left < gmPos.x + gmBox[static_cast<int>(CHECK_DIR::RIGHT)] &&
				left + width / 2 > gmPos.x - gmBox[static_cast<int>(CHECK_DIR::LEFT)] &&
				top < gmPos.y + gmBox[static_cast<int>(CHECK_DIR::DOWN)] &&
				bottom > gmPos.y - gmBox[static_cast<int>(CHECK_DIR::UP)] && (stage == gm->GetStage()))
			{
				if (rtnPos == NOTHIT)
				{
					rtnPos = gmPos.x + gmBox[static_cast<int>(CHECK_DIR::RIGHT)] + 1;
				}
				else
				{
					rtnPos = std::max(rtnPos, gmPos.x + gmBox[static_cast<int>(CHECK_DIR::RIGHT)] + 1);
				}
			}
		}
		break;
	case CHECK_DIR::RIGHT:
		for (int i = 0; i < height; i += CHIP_SIZE)
		{
			if (lpMapMng.getHitMap({ right, top + i }, stage))
			{
				if (rtnPos > right - right % CHIP_SIZE - 1 || rtnPos == NOTHIT)
				{
					rtnPos = right - right % CHIP_SIZE - 1;
				}
			}
		}

		if (lpMapMng.getHitMap({ right, bottom - 1 }, stage))
		{
			if (rtnPos > right - right % CHIP_SIZE - 1 || rtnPos == NOTHIT)
			{
				rtnPos = right - right % CHIP_SIZE - 1;
			}
		}
		for (auto& gm : gimmick)
		{
			gmPos = gm->GetPos();
			gmBox = gm->GetHitBox();
			if (left + width / 2 < gmPos.x + gmBox[static_cast<int>(CHECK_DIR::RIGHT)] &&
				right > gmPos.x - gmBox[static_cast<int>(CHECK_DIR::LEFT)] &&
				top < gmPos.y + gmBox[static_cast<int>(CHECK_DIR::DOWN)] &&
				bottom > gmPos.y - gmBox[static_cast<int>(CHECK_DIR::UP)] && (stage == gm->GetStage()))
			{
				if (rtnPos == NOTHIT)
				{
					rtnPos = gmPos.x - gmBox[static_cast<int>(CHECK_DIR::LEFT)] - 1;
				}
				else
				{
					rtnPos = std::min(rtnPos, gmPos.x - gmBox[static_cast<int>(CHECK_DIR::LEFT)] - 1);
				}
			}
		}
		break;
	case CHECK_DIR::DOWN:
		for (int i = 0; i < width; i += CHIP_SIZE)
		{
			if (lpMapMng.getHitMap({ left + i, bottom },stage))
			{
				if (rtnPos > bottom - bottom % CHIP_SIZE || rtnPos == NOTHIT)
				{
					rtnPos = bottom - bottom % CHIP_SIZE;
				}
			}
		}

		if (lpMapMng.getHitMap({ right, bottom },stage))
		{
			if (rtnPos > bottom - bottom % CHIP_SIZE || rtnPos == NOTHIT)
			{
				rtnPos = bottom - bottom % CHIP_SIZE;
			}
		}
		for (auto& gm : gimmick)
		{
			gmPos = gm->GetPos();
			gmBox = gm->GetHitBox();
			if (left < gmPos.x + gmBox[static_cast<int>(CHECK_DIR::RIGHT)] &&
				right > gmPos.x - gmBox[static_cast<int>(CHECK_DIR::LEFT)] &&
				top + height / 2 < gmPos.y + gmBox[static_cast<int>(CHECK_DIR::DOWN)] &&
				bottom > gmPos.y - gmBox[static_cast<int>(CHECK_DIR::UP)] && (stage == gm->GetStage()))
			{
				if (rtnPos == NOTHIT)
				{
					rtnPos = gmPos.y - gmBox[static_cast<int>(CHECK_DIR::UP)];
				}
				else
				{
					rtnPos = std::min(rtnPos, gmPos.y - gmBox[static_cast<int>(CHECK_DIR::UP)]);
				}
			}
		}
		break;
	case CHECK_DIR::UP:
		for (int i = 0; i < width; i += CHIP_SIZE)
		{
			if (lpMapMng.getHitMap({ left + i, top }, stage))
			{
				if (rtnPos < top + (CHIP_SIZE - top % CHIP_SIZE) + 1)
				{
					rtnPos = top + (CHIP_SIZE - top % CHIP_SIZE) + 1;
				}
			}
		}

		if (lpMapMng.getHitMap({ right, top }, stage))
		{
			if (rtnPos < top + (CHIP_SIZE - top % CHIP_SIZE) + 1)
			{
				rtnPos = top + (CHIP_SIZE - top % CHIP_SIZE) + 1;
			}
		}
		for (auto& gm : gimmick)
		{
			gmPos = gm->GetPos();
			gmBox = gm->GetHitBox();
			if (left < gmPos.x + gmBox[static_cast<int>(CHECK_DIR::RIGHT)] &&
				right > gmPos.x - gmBox[static_cast<int>(CHECK_DIR::LEFT)] &&
				top < gmPos.y + gmBox[static_cast<int>(CHECK_DIR::DOWN)] &&
				top + height / 2 > gmPos.y - gmBox[static_cast<int>(CHECK_DIR::UP)] && (stage == gm->GetStage()))
			{
				if (rtnPos == NOTHIT)
				{
					rtnPos = gmPos.y + gmBox[static_cast<int>(CHECK_DIR::DOWN)] + 1;
				}
				else
				{
					rtnPos = std::max(rtnPos, gmPos.y + gmBox[static_cast<int>(CHECK_DIR::DOWN)] + 1);
				}
			}
		}
		break;
	default:
		break;
	}

	return rtnPos;
}
