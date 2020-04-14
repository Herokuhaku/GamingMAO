#pragma once
#include "BaceScene.h"
#include "../common/Vector2.h"

class SeleScene :
	public BaceScene
{
public:
	SeleScene();
	~SeleScene();
	std::unique_ptr<BaceScene> Update(std::unique_ptr<BaceScene> own) override;

private:
	short sel;
	Vector2 arrow;
	bool arrowflag;
};

