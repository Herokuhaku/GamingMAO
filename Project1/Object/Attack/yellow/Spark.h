#pragma once
#include "../../Object.h"

class Spark :
	public Object
{
public:
	Spark() = delete;
	// pos:���W			time:���Ԏ�
	// stage:�X�e�[�W	target:�ڕW
	Spark(Vector2* pos, TIME time, int stage, OBJ_TYPE target);
	~Spark();

	void Update(void)override;
private:
	void Init(void);

	OBJ_TYPE _target;
	Vector2* _ownerPos;

	int _timer;
};

