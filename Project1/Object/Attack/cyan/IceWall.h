#pragma once
#include "../../Object.h"

class IceWall :
	public Object
{
public:
	IceWall();
	IceWall(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	~IceWall();

	void Update(void)override;

	void IfHitAttack(void)override;
private:
	void Init(void);

	OBJ_TYPE _target;
};

