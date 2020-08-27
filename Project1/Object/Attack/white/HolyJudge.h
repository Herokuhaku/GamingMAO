#pragma once
#include "../../Object.h"

class HolyJudge :
	public Object
{
public:
	HolyJudge() = delete;
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
	HolyJudge(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	~HolyJudge();

	void Update(void)override;

	void IfHitAttack(std::shared_ptr<Object> target)override;
private:
	void Init(void);

	int FindSF(int);

	int _count;

	OBJ_TYPE _target;

	static constexpr int LIFE_TIME = 220;
	static constexpr int SURFACE_LIMIT = 3000;
};

