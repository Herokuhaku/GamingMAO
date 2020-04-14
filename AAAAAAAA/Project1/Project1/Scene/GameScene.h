#pragma once
#include "BaceScene.h"

class GameScene:public BaceScene
{
public:
	GameScene();
	~GameScene();

	std::unique_ptr<BaceScene> Update(std::unique_ptr<BaceScene> own) override;
};

