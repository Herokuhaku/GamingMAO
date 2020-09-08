#include "CheckHitAttack.h"
#include "../Object/Object.h"
#include "../Object/Enemy/Enemy.h"
#include "../Object/Barrier/Barrier.h"
#include "../Audio/AudioContainer.h"

namespace
{
	AudioContainer _audio;
}

void CheckHitAttack::operator()(const std::vector<std::shared_ptr<Object>>& objlist, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist)
{
	for (const auto& attack : atklist)
	{
		for (const auto& obj : objlist)
		{
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
			
			switch (attack.first._target)
			{
			case OBJ_TYPE::ENEMY:
			case OBJ_TYPE::PLAYER:
				if (obj->getObjType() != attack.first._target)
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
			
			if (attack.first.IsHit(attack.second->getPos(), attack.second->getState().second, obj->getPos(), obj->getHitOffset()))
			{
				obj->damagingHP(attack.first._damage);
				obj->setInv(attack.first._invincibleTime);
				attack.second->IfHitAttack(obj);
			}
		}
	}
}

void CheckHitAttack::operator()(const std::vector<std::shared_ptr<Enemy>>& objlist, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist)
{
	for (const auto& attack : atklist)
	{
		for (const auto& obj : objlist)
		{
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
			
			switch (attack.first._target)
			{
			case OBJ_TYPE::ENEMY:
			case OBJ_TYPE::PLAYER:
				if (obj->getObjType() != attack.first._target)
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



			if (attack.first.IsHit(attack.second->getPos(), attack.second->getState().second, obj->getPos(), obj->getHitOffset()))
			{
				obj->damagingHP(attack.first._damage);
				obj->setInv(attack.first._invincibleTime);
				attack.second->IfHitAttack(obj);
			}
		}
	}
}

void CheckHitAttack::operator()(const std::vector<std::shared_ptr<Barrier>>& barrier, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist)
{
	for (const auto& attack : atklist)
	{
		for (const auto& b : barrier)
		{
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

			switch (attack.first._target)
			{
			case OBJ_TYPE::ENEMY:
			case OBJ_TYPE::PLAYER:
				if (b->GetOwnerType() != attack.first._target)
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

			if (attack.first.IsHit(attack.second->getPos(), attack.second->getState().second, b->GetPos(), b->GetHitOffset()))
			{
				_audio.LoadSound("sound/magic/shield_block.wav", "block", 10);
				_audio.ChangeVolume("block", 180);
				PlaySoundMem(_audio.GetSound("block"), DX_PLAYTYPE_BACK, true);
				attack.second->IfHitAttack(nullptr);
			}
		}
	}
}
