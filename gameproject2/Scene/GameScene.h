#pragma once
#include "BaceScene.h"
#include "../Obj/Object.h"
#include "../Obj/Enemy/Enemy.h"
#include "../Graphic/EffekseerMng.h"


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

