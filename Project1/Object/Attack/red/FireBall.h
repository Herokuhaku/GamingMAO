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

	void Update(void);
	void Draw(void) override;

	void IfHitAttack(std::shared_ptr<Object> target)override;

private:
	void Init(void);

	void FireballUpdate(void);
	void ExplosionUpdate(void);
	void(FireBall::*_update)(void);

	Vector2 _vec;
	OBJ_TYPE _target;

	int _timer;
};

