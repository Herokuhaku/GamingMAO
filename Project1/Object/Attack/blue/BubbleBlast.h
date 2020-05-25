#pragma once
#include "../../Object.h"

class BubbleBlast :
	public Object
{
public:
	BubbleBlast();
	BubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	~BubbleBlast();

	void Update(void)override;

	void IfHitAttack(void)override;
private:
	int _count;
	static constexpr int LIFE_TIME = 5;
};

