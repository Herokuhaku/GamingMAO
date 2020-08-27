#pragma once
#include "../../Object.h"

class IceWall :
	public Object
{
public:
	IceWall() = delete;
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
	IceWall(Vector2 pos, TIME time, int stage, OBJ_TYPE target);
	~IceWall();

	void Update(void)override;

	void IfHitAttack(std::shared_ptr<Object> target)override;
private:
	void Init(void);

	OBJ_TYPE _target;
};

