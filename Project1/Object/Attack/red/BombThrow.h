#pragma once
#include "../../Object.h"

class BombThrow :
	public Object
{
public:
	BombThrow() = delete;
	// pos:座標			dir:方向
	// speed:速度( speed > 0 でdir方向に、speed < 0 で反対側に)
	// vel:初速のY成分(負で上方向、正で下方向)
	// time:時間軸		stage:ステージ
	// target:目標
	BombThrow(Vector2 pos, DIR dir, int speed, double vel, TIME time, int stage, OBJ_TYPE target);
	~BombThrow();

	void Update(void)override;

	void IfHitAttack(void)override;
private:
	void Init(void);

	void BombUpdate(void);
	void ExplosionUpdate(void);
	void(BombThrow::*_update)(void);

	int _speed;
	double _vel;

	OBJ_TYPE _target;

	int _timer;

	static constexpr double G_ACC = 0.1;
	static constexpr double ACC_MAX = 5.0;

	static constexpr double RAD_VEL = 3.141592653589 / 128.0;

	void VelUpdate(void);
};

