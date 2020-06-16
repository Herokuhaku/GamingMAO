#pragma once
#include "BaseScene.h"

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) override;
};

