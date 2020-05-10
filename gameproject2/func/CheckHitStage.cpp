#include "CheckHitStage.h"

int CheckHitStage::operator()(const CHECK_DIR & dir, const Vector2 & pos, const std::array<int, 4>& offset)
{
	int length = offset[static_cast<int>(CHECK_DIR::LEFT)] + offset[static_cast<int>(CHECK_DIR::RIGHT)];
	int rtnPos = NOTHIT;

	switch (dir)
	{
	case CHECK_DIR::LEFT:
		if (pos.x - offset[static_cast<int>(CHECK_DIR::LEFT)] < 0)
		{
			rtnPos = 0;
		}
		else if (lpMapMng.getHitMap({ pos.x - offset[static_cast<int>(CHECK_DIR::LEFT)] + CHIP_SIZE, pos.y }))
		{
			rtnPos = pos.x - offset[static_cast<int>(CHECK_DIR::LEFT)] + (CHIP_SIZE - (pos.x - offset[static_cast<int>(CHECK_DIR::LEFT)]) % CHIP_SIZE + CHIP_SIZE);
		}
		else if (lpMapMng.getHitMap({ pos.x - offset[static_cast<int>(CHECK_DIR::LEFT)], pos.y }))
		{
			rtnPos = pos.x - offset[static_cast<int>(CHECK_DIR::LEFT)] + (CHIP_SIZE - (pos.x - offset[static_cast<int>(CHECK_DIR::LEFT)]) % CHIP_SIZE);
		}
		else
		{

		}
		break;
	case CHECK_DIR::RIGHT:
		if (lpMapMng.getHitMap({ pos.x + offset[static_cast<int>(CHECK_DIR::RIGHT)] - CHIP_SIZE, pos.y }))
		{
			rtnPos = pos.x + offset[static_cast<int>(CHECK_DIR::RIGHT)] - (pos.x + offset[static_cast<int>(CHECK_DIR::RIGHT)]) % CHIP_SIZE - 1 - CHIP_SIZE;
		}
		else if (lpMapMng.getHitMap({ pos.x + offset[static_cast<int>(CHECK_DIR::RIGHT)], pos.y }))
		{
			rtnPos = pos.x + offset[static_cast<int>(CHECK_DIR::RIGHT)] - (pos.x + offset[static_cast<int>(CHECK_DIR::RIGHT)]) % CHIP_SIZE - 1;
		}
		else
		{

		}
		break;
	case CHECK_DIR::DOWN:
		for (int i = 0; i < length; i += CHIP_SIZE)
		{
			if (lpMapMng.getHitMap({ pos.x - offset[static_cast<int>(CHECK_DIR::LEFT)] +i, pos.y }))
			{
				if (rtnPos < pos.y - pos.y % CHIP_SIZE)
				{
					rtnPos = pos.y - pos.y % CHIP_SIZE;
				}
			}
		}

		if (lpMapMng.getHitMap({ pos.x + offset[static_cast<int>(CHECK_DIR::RIGHT)], pos.y }))
		{
			if (rtnPos < pos.y - pos.y % CHIP_SIZE)
			{
				rtnPos = pos.y - pos.y % CHIP_SIZE;
			}
		}
		break;
	case CHECK_DIR::UP:
		break;
	default:
		break;
	}

	return rtnPos;
}
