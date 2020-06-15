#pragma once
#include "../../Object.h"

class ThunderCloud :
	public Object
{
public:
	ThunderCloud() = delete;
	// pos:���W				dir:����
	// speed:���x( speed > 0 ��dir�����ɁAspeed < 0 �Ŕ��Α���)
	// count:���Ƃ����̐�	dur:���̊Ԋu(�t���[����)
	// time:���Ԏ�			stage:�X�e�[�W
	// target:�ڕW
	ThunderCloud(Vector2 pos, DIR dir, int speed, int count, int dur, TIME time, int stage, OBJ_TYPE target);
	~ThunderCloud();

	void Update(void)override;
private:
	void Init(void);

	int FindSF(void);

	OBJ_TYPE _target;

	int _attackCount;
	int _countMax;

	int _attackDur;
	int _timer;

	int _speed;


};

