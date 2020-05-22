#pragma once
#include "../Object.h"
#include "../../func/CheckHitStage.h"

class FireBall :
	public Object
{
public:
	FireBall();
	FireBall(Vector2 pos, DIR dir, int speed, TIME time, int stage, OBJ_TYPE target);
	~FireBall();

	void Update(void)override;

	void IfHitAttack(void)override;

private:
	void Init(void);

	int _speed;
	OBJ_TYPE _target;
};

