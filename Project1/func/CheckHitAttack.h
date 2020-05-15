#pragma once
#include "../Scene/GameScene.h"
#include "../Object/Object.h"
#include "../Object/Enemy/Enemy.h"

struct CheckHitAttack
{
public:
	void operator()(const std::vector<std::shared_ptr<Object>>& objlist, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist);
	void operator()(const std::vector<std::shared_ptr<Enemy>>& objlist, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist);
};

