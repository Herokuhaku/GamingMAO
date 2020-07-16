#pragma once
#include "../../Object.h"
#include "../../../func/CheckHitStage.h"

class FireBall :
	public Object
{
public:
	FireBall() = delete;
	// pos:���W			dir:����
	// vec:�ړ��x�N�g��( vec.x > 0 ��dir�����ɁAvec.x < 0 �Ŕ��Α���)
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
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

