#pragma once
#include "../../Object.h"
#include "../../../func/CheckHitStage.h"

class FireBall :
	public Object
{
public:
	FireBall();
	FireBall(Vector2 pos, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target);
	~FireBall();

	void Update(void)override;

	void IfHitAttack(void)override;

private:
	void Init(void);

	Vector2 _vec;
	OBJ_TYPE _target;
};

