#pragma once
#include "../../Object.h"
#include "../../../func/CheckHitStage.h"

class FireBall :
	public Object
{
public:
	FireBall() = delete;
	// pos:座標			dir:方向
	// vec:移動ベクトル( vec.x > 0 でdir方向に、vec.x < 0 で反対側に)
	// time:時間軸		stage:ステージ
	// target:目標
	FireBall(Vector2 pos, DIR dir, Vector2 vec, TIME time, int stage, OBJ_TYPE target);
	~FireBall();

	void FireballUpdate(void);
	void ExplosionUpdate(void);
	void(FireBall::*_update)(void);
	void Update(void);

	void IfHitAttack(void)override;

private:
	void Init(void);

	Vector2 _vec;
	OBJ_TYPE _target;

	int _timer;
};

