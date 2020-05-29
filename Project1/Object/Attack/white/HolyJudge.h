#pragma once
#include "../../Object.h"

class HolyJudge :
	public Object
{
public:
	HolyJudge();
	HolyJudge(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	~HolyJudge();

	void Update(void)override;

	void IfHitAttack(void)override;
private:
	void Init(void);

	int FindSF(int);

	int _count;

	OBJ_TYPE _target;

	static constexpr int LIFE_TIME = 220;
};

