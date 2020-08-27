#include "CheckHitAttack.h"
#include "../Object/Object.h"
#include "../Object/Enemy/Enemy.h"
#include "../Object/Barrier/Barrier.h"

void CheckHitAttack::operator()(const std::vector<std::shared_ptr<Object>>& objlist, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist)
{
	for (const auto& attack : atklist)
	{
		bool flag;
		OBJ_TYPE my_type, target;
		Vector2 pos1, pos2;
		int damage, invTime;

		std::tie(flag, my_type, pos1, pos2, damage, invTime, target) = attack.first;

		pos1.x = pos1.x * (static_cast<int>(attack.second->getState().second) - 1) + attack.second->getPos().x;
		pos1.y = attack.second->getPos().y + pos1.y;
		pos2.x = pos2.x * (static_cast<int>(attack.second->getState().second) - 1) + attack.second->getPos().x;
		pos2.y = attack.second->getPos().y + pos2.y;

		if (pos1.x > pos2.x)
		{
			std::swap(pos1.x, pos2.x);
		}

		for (const auto& obj : objlist)
		{
			Vector2 objPos = obj->getPos();
			std::array<int, 4> hitBox = obj->getHitOffset();

			if (!(obj->Alive()) || attack.second->getState().first == OBJ_STATE::DEAD)
			{
				continue;
			}

			if (obj->getObjType() == OBJ_TYPE::CAMERA)
			{
				continue;
			}

			if (attack.second->getTimeLine() != obj->getTimeLine())
			{
				continue;
			}

			if (attack.second->getStage() != obj->getStage())
			{
				continue;
			}
			
			switch (target)
			{
			case OBJ_TYPE::ENEMY:
			case OBJ_TYPE::PLAYER:
				if (obj->getObjType() != target)
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
				continue;
			}

			if (obj->getHP() <= 0)
			{
				continue;
			}

			if (!attack.second->Alive())
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
				attack.second->IfHitAttack(obj);
			}
		}
	}
}

void CheckHitAttack::operator()(const std::vector<std::shared_ptr<Enemy>>& objlist, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist)
{
	for (const auto& attack : atklist)
	{
		bool flag;
		OBJ_TYPE my_type, target;
		Vector2 pos1, pos2;
		int damage, invTime;

		std::tie(flag, my_type, pos1, pos2, damage, invTime, target) = attack.first;

		pos1.x = pos1.x * (static_cast<int>(attack.second->getState().second) - 1) + attack.second->getPos().x;
		pos1.y = attack.second->getPos().y + pos1.y;
		pos2.x = pos2.x * (static_cast<int>(attack.second->getState().second) - 1) + attack.second->getPos().x;
		pos2.y = attack.second->getPos().y + pos2.y;

		if (pos1.x > pos2.x)
		{
			std::swap(pos1.x, pos2.x);
		}

		for (const auto& obj : objlist)
		{
			Vector2 objPos = obj->getPos();
			std::array<int, 4> hitBox = obj->getHitOffset();

			if(!(obj->Alive()) || !(attack.second->Alive()))
			{
				continue;
			}

			if (obj->getObjType() == OBJ_TYPE::CAMERA)
			{
				continue;
			}

			if (attack.second->getTimeLine() != obj->getTimeLine())
			{
				continue;
			}

			if (attack.second->getStage() != obj->getStage())
			{
				continue;
			}
			
			switch (target)
			{
			case OBJ_TYPE::ENEMY:
			case OBJ_TYPE::PLAYER:
				if (obj->getObjType() != target)
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
				attack.second->IfHitAttack(obj);
			}
		}
	}
}

void CheckHitAttack::operator()(const std::vector<std::shared_ptr<Barrier>>& barrier, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist)
{
	for (const auto& attack : atklist)
	{
		bool flag;
		OBJ_TYPE my_type, target;
		Vector2 pos1, pos2;
		int damage, invTime;

		std::tie(flag, my_type, pos1, pos2, damage, invTime, target) = attack.first;

		pos1.x = pos1.x * (static_cast<int>(attack.second->getState().second) - 1) + attack.second->getPos().x;
		pos1.y = attack.second->getPos().y + pos1.y;
		pos2.x = pos2.x * (static_cast<int>(attack.second->getState().second) - 1) + attack.second->getPos().x;
		pos2.y = attack.second->getPos().y + pos2.y;

		if (pos1.x > pos2.x)
		{
			std::swap(pos1.x, pos2.x);
		}

		for (const auto& b : barrier)
		{
			Vector2 bPos = b->GetPos();
			std::array<int, 4> hitBox = b->GetHitOffset();

			if (!(b->IsActive()) || b->IsDelete() || b->IsDead())
			{
				continue;
			}

			if (attack.second->getTimeLine() != b->GetTimeLine())
			{
				continue;
			}

			if (attack.second->getStage() != b->GetStage())
			{
				continue;
			}

			switch (target)
			{
			case OBJ_TYPE::ENEMY:
			case OBJ_TYPE::PLAYER:
				if (b->GetOwnerType() != target)
				{
					continue;
				}
				break;
			case OBJ_TYPE::MAX:
				if (b->GetOwnerType() == attack.second->getObjType())
				{
					continue;
				}
				break;
			default:
				break;
			}

			if (bPos.x - hitBox[static_cast<int>(CHECK_DIR::LEFT)] <= pos2.x &&
				bPos.x + hitBox[static_cast<int>(CHECK_DIR::RIGHT)] >= pos1.x &&
				bPos.y - hitBox[static_cast<int>(CHECK_DIR::UP)] <= pos2.y &&
				bPos.y + hitBox[static_cast<int>(CHECK_DIR::DOWN)] >= pos1.y)
			{
				attack.second->IfHitAttack(nullptr);
			}
		}
	}
}
