#pragma once
#include "../../Object.h"

class BombThrow :
	public Object
{
public:
	BombThrow();
	BombThrow(Vector2 pos, DIR dir, int speed, double vel, TIME time, int stage, OBJ_TYPE target);
	~BombThrow();

	void Update(void)override;

	void IfHitAttack(void)override;
private:
	void Init(void);

	int _speed;
	double _vel;

	OBJ_STATE _target;

	static constexpr double G_ACC = 0.3;
	static constexpr double ACC_MAX = 5.0;

	static constexpr double RAD_VEL = 3.141592653589 / 128.0;

	void VelUpdate(void);
};

