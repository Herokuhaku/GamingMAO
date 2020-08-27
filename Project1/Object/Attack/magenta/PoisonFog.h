#pragma once
#include "../../Object.h"


class PoisonFog :
	public Object
{
public:
	PoisonFog() = delete;
	// pos:���W			count:��������
	// time:���Ԏ�		stage:�X�e�[�W
	// target:�ڕW
	PoisonFog(Vector2 pos, int count, TIME time, int stage, OBJ_TYPE target);
	~PoisonFog();

	void Update(void)override;

	void IfHitAttack(std::shared_ptr<Object> target)override;
private:
	void Init(void);

	int _count;
	int _lifeTime;

	OBJ_TYPE _target;
};

