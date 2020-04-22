#pragma once
#include "BaceScene.h"
#include "../Object/Object.h"
#include "../Object/Enemy/Enemy.h"


class GameScene:public BaceScene
{
public:
	GameScene();
	~GameScene();

	std::unique_ptr<BaceScene> Update(std::unique_ptr<BaceScene> own) override;

private:
	bool Init(void);
	
	std::vector<std::shared_ptr<Object>>_objList;
	std::vector<std::shared_ptr<Object>> _enemyList;
};
 
