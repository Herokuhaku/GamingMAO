#pragma once
#include "BaceScene.h"
#include "../Obj/Object.h"
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

};

