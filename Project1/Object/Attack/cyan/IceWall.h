#pragma once
#include "../../Object.h"

class IceWall :
	public Object
{
public:
	IceWall() = delete;
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	IceWall(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	~IceWall();

	void Update(void)override;

	void IfHitAttack(void)override;
private:
	void Init(void);

	OBJ_TYPE _target;
};

