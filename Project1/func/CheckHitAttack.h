#pragma once
#include <memory>
#include <vector>
#include "../Scene/GameScene.h"

class Object;
class Enemy;
class Barrier;

struct CheckHitAttack
{
public:
	void operator()(const std::vector<std::shared_ptr<Object>>& objlist, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist);
	void operator()(const std::vector<std::shared_ptr<Enemy>>& objlist, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist);
	void operator()(const std::vector<std::shared_ptr<Barrier>>& barrier, const std::vector<std::pair<atkData, std::shared_ptr<Object>>>& atklist);
};

