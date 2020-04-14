#pragma once
#include "BaceScene.h"

class TitleScene :
	public BaceScene
{
public:
	TitleScene();
	~TitleScene();
	std::unique_ptr<BaceScene> Update(std::unique_ptr<BaceScene> own) override;
};

