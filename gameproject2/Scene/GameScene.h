#pragma once
#include "BaceScene.h"
#include <Object/Player.h>

class GameScene:public BaceScene
{
public:
	GameScene();
	~GameScene();

	std::unique_ptr<BaceScene> Update(std::unique_ptr<BaceScene> own) override;

	Player* player;
};


