#pragma once
#include "BaceScene.h"
#include "../Obj/Player.h"
#include "../Obj/Enemy/Enemy.h"
#include "../Obj/Enemy/s_dragon.h"

class GameScene:public BaceScene
{
public:
	GameScene();
	~GameScene();

	std::unique_ptr<BaceScene> Update(std::unique_ptr<BaceScene> own) override;

	Player* player;
	Enemy* enemy;
	s_dragon* test;
};

