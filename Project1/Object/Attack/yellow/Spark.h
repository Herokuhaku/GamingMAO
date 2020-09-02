#pragma once
#include "../../Object.h"

class Spark :
	public Object
{
public:
	Spark() = delete;
	// pos:座標			time:時間軸
	// stage:ステージ	target:目標
	Spark(Vector2* pos, TIME time, int stage, OBJ_TYPE target);
	~Spark();

	void Update(void)override;
private:
	void Init(void);

	OBJ_TYPE _target;
	Vector2* _ownerPos;

	int _timer;
};

