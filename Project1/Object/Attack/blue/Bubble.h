#pragma once
#include "../../Object.h"
#include "../AttackMng.h"



class Bubble :
	public Object
{
public:
	Bubble() = delete;
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
	Bubble(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	~Bubble();

	void Update(void)override;

	void IfHitAttack(void)override;

private:
	void Init(void);

	OBJ_TYPE _target;

	int _floatCount;

	int _basePos_y;
	
	static constexpr int LIFE_TIME = 1800;	// ��������
};

