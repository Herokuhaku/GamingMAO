#pragma once
#include "../../Object.h"

class BubbleBlast :
	public Object
{
public:
	BubbleBlast() = delete;
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	BubbleBlast(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	~BubbleBlast();

	void Update(void)override;

	void IfHitAttack(void)override;
private:
	int _count;
	static constexpr int LIFE_TIME = 5;
};

