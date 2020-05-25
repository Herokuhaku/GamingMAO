#pragma once
#include "../../Object.h"


class PoisonFog :
	public Object
{
public:
	PoisonFog();
	PoisonFog(Vector2 pos, int count, TIME time, int stage, OBJ_TYPE target);
	~PoisonFog();

	void Update(void)override;

	void IfHitAttack(void)override;
private:
	void Init(void);

	int _count;
	int _lifeTime;

	OBJ_TYPE _target;
};

