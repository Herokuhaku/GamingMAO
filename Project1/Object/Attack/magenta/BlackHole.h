#pragma once
#include "../../Object.h"

class BlackHole :
	public Object
{
public:
	BlackHole() = delete;
	// pos:���W			dir:����
	// vec:�ړ��x�N�g��( vec.x > 0 ��dir�����ɁAvec.x < 0 �Ŕ��Α���)
	// lifetime:��������
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
	BlackHole(Vector2 pos, DIR dir, Vector2 vec, int lifetime, TIME time, int stage, OBJ_TYPE target);
	~BlackHole();

	void Update(void);

	void Draw(void)override;

	void IfHitAttack(std::shared_ptr<Object> target)override;

private:
	void Init(void);

	void NormalUpdate(void);
	void FinishUpdate(void);
	void(BlackHole::* _update)(void);

	Vector2 _vec;
	OBJ_TYPE _target;

	int _lifetime;

	int _timer;
};

