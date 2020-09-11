#pragma once
#include "SpearAttack.h"

class CaneAttack :
	public SpearAttack
{

public:
	CaneAttack(Vector2& ePos, DIR dir, TIME time, int stage, OBJ_TYPE target);
	~CaneAttack() {}
	void Update(void)override;
	void IfHitAttack(std::shared_ptr<Object> target) override;
private:
	int addX;
	bool Init(void)override;
};
