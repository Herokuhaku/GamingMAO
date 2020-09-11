#pragma once
#include "SpearAttack.h"

class ThunderAttack :
	public SpearAttack
{

public:
	ThunderAttack(Vector2& ePos, DIR dir, TIME time, int stage, OBJ_TYPE target);
	~ThunderAttack() {}
	void Update(void)override;
	void IfHitAttack(std::shared_ptr<Object> target) override;
private:
	bool Init(void)override;
};
