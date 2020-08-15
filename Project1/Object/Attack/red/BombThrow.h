#pragma once
#include "../../Object.h"

class BombThrow :
	public Object
{
public:
	BombThrow() = delete;
	// pos:���W			dir:����
	// speed:���x( speed > 0 ��dir�����ɁAspeed < 0 �Ŕ��Α���)
	// vel:������Y����(���ŏ�����A���ŉ�����)
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
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

