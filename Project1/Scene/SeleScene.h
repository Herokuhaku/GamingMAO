#pragma once
#include "BaseScene.h"
#include "../common/Vector2.h"

class SeleScene :
	public BaseScene
{
public:
	SeleScene();
	~SeleScene();
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> own) override;

private:
	short sel;
	short sel2;
	Vector2 arrow;
	bool arrowflag;
};

