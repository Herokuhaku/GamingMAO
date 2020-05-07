#include "CheckHitAttack.h"

void CheckHitAttack::operator()(const std::vector<std::shared_ptr<Object>>& objlist, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist)
{
	for (auto attack : atklist)
	{
		bool flag;
		OBJ_TYPE my_type, target;
		Vector2 pos1, pos2;
		int damage, invTime;

		std::tie(flag, my_type, pos1, pos2, damage, invTime, target) = attack.first;

		pos1 = pos1 * (static_cast<int>(attack.second->getState().second) - 1) + attack.second->getPos();
		pos2 = pos2 * (static_cast<int>(attack.second->getState().second) - 1) + attack.second->getPos();

		if (pos1.x > pos2.x)
		{
			std::swap(pos1.x, pos2.x);
		}

		for (auto obj : objlist)
		{
			Vector2 objPos = obj->getPos();
			std::array<int, 4> hitBox = obj->getHitOffset();

			if (obj->getType() == OBJ_TYPE::CAMERA)
			{
				continue;
			}
			
			switch (target)
			{
			case OBJ_TYPE::ENEMY:
			case OBJ_TYPE::PLAYER:
				if (obj->getType() != target)
				{
					continue;
				}
				break;
			case OBJ_TYPE::MAX:
				if (obj == attack.second)
				{
					continue;
				}
				break;
			default:
				break;
			}

			if (obj->checkInv())
			{
				obj->InvUpdate();
				continue;
			}

			if (obj->getHP() <= 0)
			{
				continue;
			}

			if (objPos.x - hitBox[static_cast<int>(CHECK_DIR::LEFT)] <= pos2.x &&
				objPos.x + hitBox[static_cast<int>(CHECK_DIR::RIGHT)] >= pos1.x &&
				objPos.y - hitBox[static_cast<int>(CHECK_DIR::UP)] <= pos2.y &&
				objPos.y + hitBox[static_cast<int>(CHECK_DIR::DOWN)] >= pos1.y)
			{
				obj->damagingHP(damage);
				obj->setInv(invTime);
			}

		}
	}
}
